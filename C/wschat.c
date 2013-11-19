#include <cdk.h>

#ifdef HAVE_XCURSES
char *XCursesProgramName="WSChat";
#endif

/* Define some global variables. */
#define MAXHISTORY	5000
static char *introductionMessage[] = {
   "<C></B/16>  WSChat Command Line Interface  ", "",
   "<C>Written by Wenxuan Zhao", "",
   "<C>Credit: CLI code ",
   "<C>borrowed from Mike Glover", "",
   "<C>Type </B>/help<!B> to get help."};

/* This structure is used for keeping command history. */
struct history_st {
   int count;
   int current;
   char *command[MAXHISTORY];
};

/* Define some local prototypes. */
void help (CDKENTRY *entry);
static BINDFN_PROTO(historyUpCB);
static BINDFN_PROTO(historyDownCB);
static BINDFN_PROTO(viewHistoryCB);

/*
 * Written by:	Mike Glover, Wenxuan Zhao
 * Purpose:
 *		This creates a very simple command interface for WSChat.
 */
int main(int argc, char **argv)
{
   /* Declare variables. */
   CDKSCREEN *cdkscreen		= 0;
   CDKSWINDOW *commandOutput	= 0;
   CDKENTRY *commandEntry	= 0;
   WINDOW *cursesWin		= 0;
   chtype *convert		= 0;
   char *command		= 0;
   char *upper			= 0;
   char *prompt			= "</B/24>>";
   char *title			= "<C></B/5>WSChat Message Board";
   int promptLen		= 0;
   int commandFieldWidth	= 0;
   struct history_st history;
   char temp[600];
   int ret, junk;

   /* Set up the history. */
   history.current = 0;
   history.count = 0;

   /* Check the command line for options. */
   while (1)
   {
      /* Are there any more command line options to parse. */
      if ((ret = getopt (argc, argv, "t:p:")) == -1)
      {
	 break;
      }
      switch (ret)
      {
	 case 'p':
	      prompt = copyChar (optarg);
	      break;

	 case 't':
	      title = copyChar (optarg);
	      break;

	 default:
	      break;
      }
   }

   /* Set up CDK. */
   cursesWin = initscr();
   cdkscreen = initCDKScreen (cursesWin);

   /* Start color. */
   initCDKColor();

   /* Create the scrolling window. */
   commandOutput = newCDKSwindow (cdkscreen, CENTER, TOP, -8, -2,
					title, 1000, TRUE, FALSE);

   /* Convert the prompt to a chtype and determine its length. */
   convert = char2Chtype (prompt, &promptLen, &junk);
   commandFieldWidth = COLS - promptLen - 4;
   freeChtype (convert);

   /* Create the entry field. */
   commandEntry = newCDKEntry (cdkscreen, CENTER, BOTTOM,
				0, prompt, A_BOLD|COLOR_PAIR(8), COLOR_PAIR(24)|'_',
				vMIXED, commandFieldWidth, 1, 512, FALSE, FALSE);

   /* Create the key bindings. */
   bindCDKObject (vENTRY, commandEntry, KEY_UP, historyUpCB, &history);
   bindCDKObject (vENTRY, commandEntry, KEY_DOWN, historyDownCB, &history);
   bindCDKObject (vENTRY, commandEntry, KEY_TAB, viewHistoryCB, commandOutput);

   /* Draw the screen. */
   refreshCDKScreen (cdkscreen);

   /* Show them who wrote this and how to get help. */
   popupLabel (cdkscreen, introductionMessage, 8);
   eraseCDKEntry (commandEntry);

   /* Show welcome */
   addCDKSwindow (commandOutput, "</B/32>Welcome!", BOTTOM);
/* COLORs' are great!
   int i;
   for (i = 0; i <= 64; i++)
   {
      sprintf (temp, "%d: </B/%d>Welcome!", i, i);
      addCDKSwindow (commandOutput, temp, BOTTOM);
   }
*/

   /* Do this forever. */
   for (;;)
   {
      /* Get the command. */
      drawCDKEntry (commandEntry, ObjOf(commandEntry)->box);
      command	= activateCDKEntry (commandEntry, 0);

      /* Check the output of the command. */
      if (strcmp (command, "/quit") == 0 ||
		strcmp (command, "/exit") == 0 ||
		commandEntry->exitType == vESCAPE_HIT)
      {
	 /* All done. */
	 freeChar (upper);

	 while (history.count-- > 0)
	    free (history.command[history.count]);

	 destroyCDKEntry (commandEntry);
	 destroyCDKSwindow (commandOutput);
	 destroyCDKScreen (cdkscreen);

	 endCDK();

	 exit(EXIT_SUCCESS);
      }
      else if (strcmp (command, "/clear") == 0)
      {
	 /* Keep the history. */
	 history.command[history.count] = copyChar (command);
	 history.count++;
	 history.current = history.count;
	 cleanCDKSwindow (commandOutput);
	 cleanCDKEntry (commandEntry);
      }
      else if (strcmp (command, "/help") == 0)
      {
	 /* Keep the history. */
	 history.command[history.count] = copyChar (command);
	 history.count++;
	 history.current = history.count;

	 /* Display the help. */
	 help (commandEntry);

	 /* Clean the entry field. */
	 cleanCDKEntry (commandEntry);
	 eraseCDKEntry (commandEntry);
      }
      else
      {
	 /* Keep the history. */
	 history.command[history.count] = copyChar (command);
	 history.count++;
	 history.current = history.count;

	 /* Jump to the bottom of the scrolling window. */
	 jumpToLineCDKSwindow (commandOutput, BOTTOM);

	 /* Insert a line providing the command. */
	 sprintf (temp, "</B>DEBUG Send: </!B>%s", command); /* TODO DEBUG */
	 addCDKSwindow (commandOutput, temp, BOTTOM);

/* TODO send */

	 /* Clean out the entry field. */
	 cleanCDKEntry (commandEntry);
      }

      /* Clean up a little. */
      freeChar (upper);
   }
}

/*
 * This is the callback for the down arrow.
 */
static int historyUpCB (EObjectType cdktype GCC_UNUSED, void *object, void *clientData, chtype key GCC_UNUSED)
{
   CDKENTRY *entry = (CDKENTRY *)object;
   struct history_st *history = (struct history_st *) clientData;

   /* Make sure we don't go out of bounds. */
   if (history->current == 0)
   {
      Beep();
      return (FALSE);
   }

   /* Decrement the counter. */
   history->current--;

   /* Display the command. */
   setCDKEntryValue (entry, history->command[history->current]);
   drawCDKEntry (entry, ObjOf(entry)->box);
   return (FALSE);
}

/*
 * This is the callback for the down arrow.
 */
static int historyDownCB (EObjectType cdktype GCC_UNUSED, void *object, void *clientData, chtype key GCC_UNUSED)
{
   CDKENTRY *entry = (CDKENTRY *)object;
   struct history_st *history = (struct history_st *) clientData;

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
      cleanCDKEntry (entry);
      drawCDKEntry (entry, ObjOf(entry)->box);
      return (FALSE);
   }

   /* Display the command. */
   setCDKEntryValue (entry, history->command[history->current]);
   drawCDKEntry (entry, ObjOf(entry)->box);
   return (FALSE);
}

/*
 * This callback allows the user to play with the scrolling window.
 */
static int viewHistoryCB (EObjectType cdktype GCC_UNUSED, void *object, void *clientData, chtype key GCC_UNUSED)
{
   CDKSWINDOW *swindow	= (CDKSWINDOW *)clientData;
   CDKENTRY *entry	= (CDKENTRY *)object;

   /* Let them play... */
   activateCDKSwindow (swindow, 0);

   /* Redraw the entry field. */
   drawCDKEntry (entry, ObjOf(entry)->box);
   return (FALSE);
}

/*
 * This function displays help.
 */
void help (CDKENTRY *entry)
{
   char *mesg[25];

   /* Create the help message. */
   mesg[0] = "<C></B/29>Help";
   mesg[1] = "";
   mesg[2] = "</B/24>When in the message inputfield";
   mesg[3] = "</24>   Key:";
   mesg[4] = "<B=Up Arrow  > Scrolls back one message.";
   mesg[5] = "<B=Down Arrow> Scrolls forward one message.";
   mesg[6] = "<B=Tab       > Activates the scrolling window.";
   mesg[7] = "</24>   Command:";
   mesg[8] = "<B=/help     > Displays this help window.";
   mesg[9] = "";
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
   popupLabel (ScreenOf(entry), mesg, 21);
}
