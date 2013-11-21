#include <cdk.h>
#include <libwebsockets.h>
#include <pthread.h>

#ifdef HAVE_XCURSES
char *XCursesProgramName="WSChat";
#endif

#ifndef WS_ADDRESS
#define WS_ADDRESS "tunnel.vince.im"
#endif

#ifndef WS_PORT
#define WS_PORT 8999
#endif

/* Define some global variables */
#define MAXHISTORY 5000
static char *introductionMessage[] = {
    "<C></B/16>  WSChat Command Line Interface  ", "",
    "<C>Written by Wenxuan Zhao", "",
    "<C>Credit: CLI code ",
    "<C>borrowed from Mike Glover", "",
    "<C>Type </B>/help<!B> to get help."};
static char *failInitMessage[] = {
    "<C></B/16>Error", "",
    "<C>  Failed to initialize WebSocket!  "
};
static char *failWSMessage[] = {
    "<C></B/16>Error", "",
    "<C>  WebSocket execution error!  "
};

/* This structure is used for keeping command history */
struct history_st {
    int count;
    int current;
    char *command[MAXHISTORY];
};

/* Define some local prototypes */
void help(CDKENTRY *entry);
static BINDFN_PROTO(historyUpCB);
static BINDFN_PROTO(historyDownCB);
static BINDFN_PROTO(viewHistoryCB);
static int callback_chat(struct libwebsocket_context *context,
    struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason,
    void *user, void *in, size_t len);
void * ws_thread_code(void *p);
void output(char *out);

/* Per session data for chat */
#define MAX_CHAT_PAYLOAD 1400
struct per_session_data__chat {
    unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + MAX_CHAT_PAYLOAD
        + LWS_SEND_BUFFER_POST_PADDING];
    unsigned int len;
    unsigned int index;
};

/* WebSocket chat protocol handler */
static struct libwebsocket_protocols protocols[] = {
    {
        "default",                            /* name */
        callback_chat,                        /* callback */
        sizeof(struct per_session_data__chat) /* per_session_data_size */
    }, {NULL, NULL, 0}                        /* End of list */
};

/* Output shared buffer and reference */
#define OUTPUT_BUF_SIZE 1024
static CDKSCREEN *cdkscreen      = 0;
static CDKSWINDOW *commandOutput = 0;
static CDKENTRY *commandEntry    = 0;
pthread_mutex_t outputLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t writeLock = PTHREAD_MUTEX_INITIALIZER;

/* shared context reference */
static struct libwebsocket_context *context;

/* shared thread reference */
static pthread_t ws_thread;
static char sendBuf[MAX_CHAT_PAYLOAD];

/* shared flag */
static int force_exit = 0;
static int ready = 0;
static int needSend = 0;

/*
 * Written by:        Mike Glover, Wenxuan Zhao
 * Purpose:
 *                    This creates a very simple command interface for WSChat.
 */
int
main(int argc, char **argv)
{
    /* Declare variables for GUI */
    WINDOW *cursesWin            = 0;
    chtype *convert              = 0;
    char *command                = 0;
    char *prompt                 = "</B/24>>";
    char *title                  = "<C></B/5>WSChat Message Board";
    int promptLen                = 0;
    int commandFieldWidth        = 0;
    struct history_st history;
    int junk;

    /* Declare variables for WebSocket */
    struct lws_context_creation_info info;
    struct libwebsocket *wsi;

    /* Disable libwebsocket output to console (which mess up the GUI) */
    lws_set_log_level(0, NULL);

    /* Initialize the WebSocket */
    memset(&info, 0, sizeof info);

    info.port                    = CONTEXT_PORT_NO_LISTEN;
    info.iface                   = NULL;
    info.protocols               = protocols;
    info.gid                     = -1;
    info.uid                     = -1;
    info.options                 = 0;

    /* Create context and try to connect */
    context = libwebsocket_create_context(&info);

    if (context)
    {
        wsi = libwebsocket_client_connect(context, WS_ADDRESS, WS_PORT, 0, "/",
            WS_ADDRESS, "origin", NULL, -1);
    }

    /* Set up the history */
    history.current = 0;
    history.count = 0;

    /* Set up CDK */
    cursesWin = initscr();
    cdkscreen = initCDKScreen(cursesWin);

    /* Start color */
    initCDKColor();

    /* Create the scrolling window */
    commandOutput = newCDKSwindow(cdkscreen, CENTER, TOP, -8, -2,
        title, 1000, TRUE, FALSE);

    /* Convert the prompt to a chtype and determine its length */
    convert = char2Chtype(prompt, &promptLen, &junk);
    commandFieldWidth = COLS - promptLen - 4;
    freeChtype(convert);

    /* Create the entry field */
    commandEntry = newCDKEntry(cdkscreen, CENTER, BOTTOM,
        0, prompt, A_BOLD|COLOR_PAIR(8), COLOR_PAIR(24)|'_',
        vMIXED, commandFieldWidth, 1, 512, FALSE, FALSE);

    /* Create the key bindings */
    bindCDKObject(vENTRY, commandEntry, KEY_UP, historyUpCB, &history);
    bindCDKObject(vENTRY, commandEntry, KEY_DOWN, historyDownCB, &history);
    bindCDKObject(vENTRY, commandEntry, KEY_TAB, viewHistoryCB, commandOutput);

    /* Draw the screen */
    refreshCDKScreen(cdkscreen);

    /* Test WebSocket initialize failure */
    if (context == NULL || wsi == NULL
        || pthread_create(&ws_thread, NULL, ws_thread_code, NULL))
    {
        popupLabel(cdkscreen, failInitMessage, 3);
        while (history.count-- > 0)
            free(history.command[history.count]);

        destroyCDKEntry(commandEntry);
        destroyCDKSwindow(commandOutput);
        destroyCDKScreen(cdkscreen);

        endCDK();

        exit(EXIT_FAILURE);
    }

    /* Show them who wrote this and how to get help */
    popupLabel(cdkscreen, introductionMessage, 8);
    eraseCDKEntry(commandEntry);

    /* Show welcome */
    output("</B/32>Welcome!");
    ready = 1;
/* COLORs' are great!
   int i;
   for (i = 0; i <= 64; i++)
   {
      sprintf(temp, "%d: </B/%d>Welcome!", i, i);
      addCDKSwindow(commandOutput, temp, BOTTOM);
   }
*/

    /* Event loop - do this forever until exit */
    for (;;)
    {
        /* Get the command */
        drawCDKEntry(commandEntry, ObjOf(commandEntry)->box);
        command = activateCDKEntry(commandEntry, 0);

        /* Check the output of the command */
        if (strcmp(command, "/quit") == 0 ||
            strcmp(command, "/exit") == 0 ||
            commandEntry->exitType == vESCAPE_HIT)
        {
            force_exit = 1;
        }
        else if (strcmp(command, "/clear") == 0)
        {
            /* Keep the history */
            history.command[history.count] = copyChar(command);
            history.count++;
            history.current = history.count;
            cleanCDKSwindow(commandOutput);
            cleanCDKEntry(commandEntry);
        }
        else if (strcmp(command, "/help") == 0)
        {
            /* Keep the history */
            history.command[history.count] = copyChar(command);
            history.count++;
            history.current = history.count;

            /* Display the help */
            help(commandEntry);

            /* Clean the entry field */
            cleanCDKEntry(commandEntry);
            eraseCDKEntry(commandEntry);
        }
        else
        {
            /* Keep the history */
            history.command[history.count] = copyChar(command);
            history.count++;
            history.current = history.count;

            /* Jump to the bottom of the scrolling window */
            jumpToLineCDKSwindow(commandOutput, BOTTOM);

            /* Write send buffer */
            pthread_mutex_lock(&writeLock);
            snprintf(sendBuf, MAX_CHAT_PAYLOAD, "%s", command);
            pthread_mutex_unlock(&writeLock);
            needSend = 1;

            /* Clean out the entry field */
            cleanCDKEntry(commandEntry);
        }

        /* Clean up before exit */
        if (force_exit)
        {
            while (history.count-- > 0)
                free(history.command[history.count]);

            pthread_join(ws_thread, NULL);
            libwebsocket_context_destroy(context);

            destroyCDKEntry(commandEntry);
            destroyCDKSwindow(commandOutput);
            destroyCDKScreen(cdkscreen);

            endCDK();

            exit(EXIT_SUCCESS);
        }
    }

    /* shouldn't get here unless something happends */
    return EXIT_FAILURE;
}

void output(char *out)
{
    pthread_mutex_lock(&outputLock);
    addCDKSwindow(commandOutput, out, BOTTOM);
    pthread_mutex_unlock(&outputLock);
}

void *
ws_thread_code(void *p)
{
    int ret;

    while (!force_exit)
    {
        /* Pause the service if not ready */
        while (!ready)
            usleep(1000);

        /* Write if needed */
        libwebsocket_callback_on_writable_all_protocol(&protocols[0]);

        /* Execute libwebsocket service */
        ret = libwebsocket_service(context, 10);

        /* Test libwebsocket execution failure */
        if (ret < 0)
        {
            popupLabel(cdkscreen, failWSMessage, 3);
            force_exit = 1;
        }
    }

    return NULL;
}

/* WebSocket chat callback function */
static int
callback_chat(struct libwebsocket_context *context, struct libwebsocket *wsi,
    enum libwebsocket_callback_reasons reason,
    void *user, void *in, size_t len)
{
    struct per_session_data__chat *pss = (struct per_session_data__chat *)user;
    int n;

    switch (reason)
    {
      /* Event Callback - onopen() */
      case LWS_CALLBACK_CLIENT_ESTABLISHED:
        output("[Client has connected]");
        pss->index = 0;
        break;

      /* Event Callback - onmessage() */
      case LWS_CALLBACK_CLIENT_RECEIVE:
        output((char *)in);
        break;

      /* Event Callback - onsend() */
      case LWS_CALLBACK_CLIENT_WRITEABLE:
        /* we will send our packet... if needed */
        if (needSend)
        {
            needSend = 0;
            pthread_mutex_lock(&writeLock);
            pss->len = sprintf((char *)&pss->buf[LWS_SEND_BUFFER_PRE_PADDING],
                "%s", sendBuf);
            pthread_mutex_unlock(&writeLock);
            n = libwebsocket_write(wsi, &pss->buf[LWS_SEND_BUFFER_PRE_PADDING],
                pss->len, LWS_WRITE_TEXT);

            if (n < 0)
            {
                output("[Error when writing to socket, hanging up]");
                return 1;
            }
        }
        break;
      default:
        break;
    }

    return 0;
}

/*
 * This is the callback for the down arrow.
 */
static int
historyUpCB(EObjectType cdktype GCC_UNUSED, void *object, void *clientData,
    chtype key GCC_UNUSED)
{
    CDKENTRY *entry              = (CDKENTRY *)object;
    struct history_st *history   = (struct history_st *) clientData;

    /* Make sure we don't go out of bounds. */
    if (history->current == 0)
    {
        Beep();
        return (FALSE);
    }

    /* Decrement the counter. */
    history->current--;

    /* Display the command. */
    setCDKEntryValue(entry, history->command[history->current]);
    drawCDKEntry(entry, ObjOf(entry)->box);
    return (FALSE);
}

/*
 * This is the callback for the down arrow.
 */
static int
historyDownCB(EObjectType cdktype GCC_UNUSED, void *object, void *clientData,
    chtype key GCC_UNUSED)
{
    CDKENTRY *entry              = (CDKENTRY *)object;
    struct history_st *history   = (struct history_st *) clientData;

    /* Make sure we don't go out of bounds. */
    if (history->current == history->count)
    {
        Beep();
        return (FALSE);
    }

    /* Increment the counter... */
    history->current++;

    /* If we are at the end, clear the entry field. */
    if (history->current == history->count)
    {
        cleanCDKEntry(entry);
        drawCDKEntry(entry, ObjOf(entry)->box);
        return (FALSE);
    }

    /* Display the command. */
    setCDKEntryValue(entry, history->command[history->current]);
    drawCDKEntry(entry, ObjOf(entry)->box);
    return (FALSE);
}

/*
 * This callback allows the user to play with the scrolling window.
 */
static int
viewHistoryCB(EObjectType cdktype GCC_UNUSED, void *object, void *clientData,
    chtype key GCC_UNUSED)
{
    CDKSWINDOW *swindow          = (CDKSWINDOW *)clientData;
    CDKENTRY *entry              = (CDKENTRY *)object;

    /* Let them play... */
    activateCDKSwindow(swindow, 0);

    /* Redraw the entry field. */
    drawCDKEntry(entry, ObjOf(entry)->box);
    return (FALSE);
}

/*
 * This function displays help.
 */
void
help(CDKENTRY *entry)
{
    char *mesg[25];

    /* Create the help message. */
    mesg[0]  = "<C></B/29>Help";
    mesg[1]  = "";
    mesg[2]  = "</B/24>When in the message inputfield";
    mesg[3]  = "</24>   Key:";
    mesg[4]  = "<B=Up Arrow  > Scrolls back one message.";
    mesg[5]  = "<B=Down Arrow> Scrolls forward one message.";
    mesg[6]  = "<B=Tab       > Activates the scrolling window.";
    mesg[7]  = "</24>   Command:";
    mesg[8]  = "<B=/help     > Displays this help window.";
    mesg[9]  = "";
    mesg[10] = "</B/24>When in the scrolling window";
    mesg[11] = "</24>   Key:";
    mesg[12] = "<B=l or L    > Loads a file into the window.";
    mesg[13] = "<B=s or S    > Saves the contents of the window to a file.";
    mesg[14] = "<B=Up Arrow  > Scrolls up one line.";
    mesg[15] = "<B=Down Arrow> Scrolls down one line.";
    mesg[16] = "<B=Page Up   > Scrolls back one page.";
    mesg[17] = "<B=Page Down > Scrolls forward one page.";
    mesg[18] = "<B=Tab/Escape> Returns to the command line.";
    mesg[19] = "";
    mesg[20] = "<C> </B/24>Have fun! ;-)<!B!24>";
    popupLabel(ScreenOf(entry), mesg, 21);
}
