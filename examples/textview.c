
#include <stdio.h>
#include <stdlib.h>
#include <wctk/wctk.h>
#include <sys/time.h>
#include <math.h>

char phrack_intro[] =
"                                  _  _       _______ \n"
"                                 | \\/ |     / _____/ \n"
"                                 |_||_|etal/ /hop\n"
"                                 _________/ /\n"
"                                /__________/\n"
"                                 (314)432-0756\n"
"                         24 Hours A Day, 300/1200 Baud\n"
"\n"
"                                  Presents....\n"
"\n"
"                                ==Phrack Inc.==\n"
"                     Volume One, Issue One, Phile 1 of 8\n"
"\n"
"                                Introduction...\n"
"\n"
"Welcome to the Phrack Inc. Philes.  Basically, we are a group of phile writers\n"
"who have combined our philes and are distributing them in a group.  This\n"
"newsletter-type project is home-based at Metal Shop.  If you or your group are\n"
"interested in writing philes for Phrack Inc. you, your group, your BBS, or any\n"
"other credits will be included.  These philes may include articles on telcom\n"
"(phreaking/hacking), anarchy (guns and death & destruction) or kracking.  Other\n"
"topics will be allowed also to an certain extent.  If you feel you have some\n"
"material that's original, please call and we'll include it in the next issue\n"
"possible.  Also, you are welcomed to put up these philes on your BBS/AE/Catfur/\n"
"Etc.  The philes will be regularly available on Metal Shop.  If you wish to say\n"
"in the philes that your BBS will also be sponsering Phrack Inc., please leave\n"
"feedback to me, Taran King stating you'd like your BBS in the credits.  Later\n"
"on.\n"
"\n"
"                                            TARAN KING\n"
"                                            2600 CLUB!\n"
"                                         METAL SHOP SYSOP\n"
"\n"
"\n"
"This issue is Volume One, Issue One, released on November 17, 1985.  Included\n"
"are:\n"
"1  This Introduction to Phrack Inc. by Taran King\n"
"2  SAM Security Article by Spitfire Hacker\n"
"3  Boot Tracing on Apple by Cheap Shades\n"
"4  The Fone Phreak's Revenge by Iron Soldier\n"
"5  MCI International Cards by Knight Lightning\n"
"6  How to Pick Master Locks by Gin Fizz and Ninja NYC\n"
"7  How to Make an Acetylene Bomb by The Clashmaster\n"
"8  School/College Computer Dial-Ups by Phantom Phreaker\n"
"\n"
"Call Metal Shop and leave feedback saying the phile topic and where you got\n"
"these philes to get your article in Phrack Inc.\n";

char phrack_issue1[] = 
"\n"
"\n"
"                                ==Phrack Inc.==\n"
"                     Volume One, Issue One, Phile 3 of 8\n"
"\n"
"//////////////////////////////////////////////////////////////////////////////\n"
"/                                                                            /\n"
"/                           Boot Tracing Made Easy                           /\n"
"/                                 Written by                                 /\n"
"/                              ________________                              /\n"
"/                              \\Cheap/ \\Shades/                              /\n"
"/                               \\___/   \\____/                               /\n"
"/                                 2600 CLUB!                                 /\n"
"/                                                                            /\n"
"//////////////////////////////////////////////////////////////////////////////\n"
"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n"
"\\                                     \\\n"
"\\           Be sure to call           \\\n"
"\\                                     \\\n"
"\\  Kleptic Palice......(314)527-5551  \\\n"
"\\    5 Meg BBS/AE/CF                  \\\n"
"\\  Metal Shop..........(314)432-0756  \\\n"
"\\    Elite BBS  (Home of 2600 CLUB!   \\\n"
"\\                and Phrack Inc. )    \\\n"
"\\                                     \\\n"
"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n"
"\n"
"About 3 or four years ago, a real good friend of mine was teaching a ML\n"
"Programming course for the Apple 2 series.  I, being a good friend and\n"
"quite bored, asked him about cracking Apple games.  He told me that he had\n"
"spent the last summer cracking programs.  He showed me a method that he came\n"
"up with entirely on his own, boot tracing.  Little did he know that this was\n"
"already quite popular but he developed his own method for doing it which from\n"
"reading other files about it, is the simplest I've ever seen.  (To give you\n"
"an idea, I had SN0GGLE (I've never played the game but a friend had it on\n"
"disk.) completely loaded into memory ready to be dumped in about 12 minutes.)\n"
"Ok, first of all, ALL programs can be boot traced. The only thing is that some\n"
"may not be easily converted into files.  The only programs that you should try\n"
"if you aren't real good at ML, are ones that load completely into memory. Also\n"
"to do this you will need a cassette recorder. (don't worry the program we will\n"
"save won't take too long to save, and if all goes well it will only be saved\n"
"loaded once.) I hate learning the theory behind anything so I'm not gonna\n"
"give any theory behind this. If you want the theory, read some other phile\n"
"that does this the hard way.\n"
"\n"
"First make sure your cassette recoder works by BLOADing some program and\n"
"typing:\n"
"CALL -151\n"
"AA60.AA73\n"
"You'll see something that looks like this:\n"
"AA60-30 02 xx xx xx xx xx xx\n"
"AA68-xx xx xx xx xx xx xx xx\n"
"AA70-xx xx 00 08\n"
"or whatever...The 30 02 is the length ($0230 bytes). The 00 08 is the starting\n"
"address ($0800).  Oh well, now you need to try and save the program. Type:\n"
"800.A2FW   (A2F=$800+$230-1)\n"
"1000<800.A2FM\n"
"800:00 N 801<800.A2FM\n"
"800.A2FR\n"
"1000<800.A2FV\n"
"\n"
"Once you are sure that the cassette works, (by the way do be stupid and try\n"
"that on a //c!) we can get to the good stuff...\n"
"First move the ROM boot-up code into RAM...(all steps will be from the\n"
"monitor * prompt.)\n"
"8600<C600.C6FFM\n"
"86F9:5C FF\n"
"(Now load in step 1 of the boot.)\n"
"8600G\n"
"C0E8  (turn the drive off)\n"
"(Now you have successfully loaded in track 0 sector 0) Now since we won't want\n"
"to overwrite what we've loaded in this time, Type:\n"
"8500<800.8FFM\n"
"86F9:01 85\n"
"8501L\n"
"Lets see what you've gotten...\n"
"First see if they move this part into the keyboard buffer. (A lot of programs\n"
"do this and the boot trace files that I've read don't even deal with this.)\n"
"LDX 00\n"
"LDA 800,X\n"
"STA 200,X\n"
"INX\n"
"BNE $803\n"
"JMP $211  (or any $2xx)\n"
"(sometimes done with Y's instead of X's.)\n"
"Then the next part will scramble what's in $08xx. but we don't have to worry\n"
"about that. Anyways find that JMP $2xx and change it to 4C xx 85 leaving the\n"
"xx the same. Usually this will be the next address but just to be safe...\n"
"Ok, now scan the code for any other JMP's if you find one that's direct\n"
"(indirect ones have the address in parenthesis) change it to 4C 5C FF, but\n"
"write down the location that it used to jump to first so you know where to\n"
"look.  It'll probably be 301 or B700. If it's the B700, you got lucky.  If it's\n"
"the 301 then you've got some more work ahead. If it was an indirect JMP, most\n"
"likely it was JMP ($003E). No if you change that to 4C 5C FF then check 3E\n"
"from monitor you'll find that 3E is 00 and 3F is 3E...Monitor uses that\n"
"place in zero page for its current memory location. So what you need to do is\n"
"8400:A5 3F 00 20 DA FD A5 3E 20 DA FD 4C 5C FF\n"
"then change that indirect jump to\n"
"85xx:4C 00 84\n"
"(by the way if the indirect jump is anything other than 3E then most likely\n"
"you can can just look at it from monitor if not write a little routine like\n"
"the one above to print out the address hidden. (Oh, check the location after\n"
"the next run. For now change it to 4C 5C FF.))\n"
"Anyways this little game will probably go on no longer than 2 or 3 loads, each\n"
"time just move the newly loaded part to another part of memory and change the\n"
"jump to jump to monitor (4C 5C FF) and the jump from the part before it to\n"
"go to the moved code.\n"
"When you find the part that JMP's up to a high area of memory (usually $B700)\n"
"you're almost done. The exit routine of the will most likely be the start of\n"
"the program.  Once you intercept it there, all you have to do now is save it to\n"
"cassette and re-load DOS.  The starting address for saving should be the\n"
"address that the B700 routine exits through. If this is higher than $6000 then\n"
"start saving at $2000 to get the Hi-Res pictures. Using WXYZ as your starting\n"
"address type:\n"
"WXYZ.9CFFW   (This will have the main program.)\n"
"800.WXYZW    (Save this are in case there is something needed down here we\n"
"              don't have to start over from scratch.)\n"
"Ok now reboot:\n"
"C600G   (with a DOS disk in the drive!)\n"
"CALL -151\n"
"WXYZ.9CFFR\n"
"Bsave PROGRAM,A$WXYZ,L$(Whatever 9CFF-WXYZ+1 is)\n"
"If the it gives you an error the file is too big. A quick DOS patch to fix\n"
"that is:\n"
"A964:FF\n"
"and try again.\n"
"Now that the program is saved, try and run it. (It's a good idea to take the\n"
"disk out of the drive, there's no telling what the program might try and do\n"
"if it sees that DOS is loaded in.)\n"
"WXYZG\n"
"(If it works, just to make sure that it's a good crack, power down the system\n"
"and try and BRUN it after a cold boot.)\n"
"If your saved the pictures with the program, most likely, it won't run. You\n"
"need to add a JMP at 1FFD to JMP to the main program. Then re-BSAVE it with a\n"
"starting address of A$1FFD, and add 3 to the length.  If the program tries to\n"
"go to the drive while its running, I'd suggest giving up unless you really\n"
"understand non-DOS disk usage. (but if you did you probably wouldn't be\n"
"reading this.)  If you get a break at an address less than $2000 then you need\n"
"to load in the second program that you saved to cassette. Put a jump in at\n"
"$800 to the main program and save the whole damn thing. If it still don't work\n"
"you're gonna need to really get fancy.\n"
"Now that you've got the thing running, it's time to figure out what is used and\n"
"what is just wasted memory. This is where I really can't help you but just\n"
"make sure that you keep a working copy and before every test power down the\n"
"machine to clear anything that might be remaining.\n"
"\n"
"Have phun and good luck.....\n"
"                      ________________\n"
"                      \\Cheap/ \\Shades/\n"
"                       \\___/   \\____/\n"
"                         2600 CLUB!\n"
"\n"
"Be sure and get a copy of PHRACK INC., available on finer BBS/AE's everywhere.\n";


/*
wctk_textview_colors_t
 tv_colors = 
{
  .default_cpair         = WCTKC_WHITE_BLACK,
  .default_hline_cpair   = WCTKC_BLACK_WHITE,
  .default_cursor_cpair  = WCTKC_WHITE_BLACK,
  .focus_hline_cpair     = WCTKC_WHITE_RED,
  .focus_cursor_cpair    = WCTKC_RED_YELLOW
};
*/

#define WINDOW_UID_MAIN         1
#define WINDOW_UID_MAIN2        2
#define WINDOW_UID_EVENT        3
#define WIDGET_UID_TEXTVIEW     1
#define NBTN                    4

char *event_type[] = 
{
  "WCTK_EVENT_NONE",
  "WCTK_EVENT_KEY",
  "WCTK_EVENT_MOUSE",
  "WCTK_EVENT_DRAG",
  "WCTK_EVENT_RESIZE",
  "WCTK_EVENT_CLOSE",
  "WCTK_EVENT_BUTTON"
};

char *widget_type[] = 
{
  "BUTTON",
  "TEXTVIEW",
  "STATICTEXT"
};

int
 main (int argc, char *const argv[])
{
  pwctk_window_t window1 = NULL;
  pwctk_window_t window2 = NULL;
  pwctk_button_t btn[NBTN];
  pwctk_static_text_t textview1 = NULL;
  pwctk_static_text_t textview2 = NULL;
  pwctk_window_t window3 = NULL;
  pwctk_static_text_t statictxt = NULL;
  wctk_event_t ev;
  struct timeval c, s;
  unsigned int run = 1, i;
  char tmp[20];
  char evdesc[256];
  (void)argc;
  (void)argv;

  wctk_init ();
  wctk_setup_colors ();

  window1 = wctk_window_create ("Phrack introduction", 3, 3, 30, 15, WCTK_WINDOW,
      WINDOW_UID_MAIN);
  window2 = wctk_window_create ("Phrack Issue 1", 5, 5, 30, 15, WCTK_WINDOW,
      WINDOW_UID_MAIN2);
  window3 = wctk_window_create ("Last event", 20, 10, 40, 10, WCTK_WINDOW_TOP, 
      WINDOW_UID_EVENT);
  textview1 = wctk_static_text_create (phrack_intro, 0, 0, 50, 10, window1);
  textview2 = wctk_static_text_create (phrack_issue1, 0, 0, 50, 10, window2);
  statictxt = wctk_static_text_create ("Wating a valid event...", 0, 0, 50, 10, window3);

  for (i = 0; i < NBTN; i++)
  {
    sprintf (tmp, "Button %i", i);
    btn[i] = wctk_button_create (tmp, 1+i*12, 8, 10, 3, 0, window1, i+1);
  }

  gettimeofday (&s, NULL);

  while (run)
  {
    wctk_event_get (&ev);
    wctk_event_translate (&ev);
    switch (ev.type)
    {
      case WCTK_EVENT_KEY:
        if (ev.data == 'q')
          run = 0;
        break;

      case WCTK_EVENT_RESIZE:
        if (ev.window == window1)
        {
          wctk_static_text_resize (textview1, window1->width-2, window1->height-10);
          for (i = 0; i < NBTN; i++)
            wctk_button_move (btn[i], 1+i*12, textview1->height+3);
        }
        else if (ev.window == window2)
        {
          wctk_static_text_resize (textview2, window2->width-2, window2->height-2);
        }
        break;
    }

    gettimeofday (&c, NULL);
  
    if (ev.data != ERR)
    {
      pwctk_window_t window = wctk_zorder_get_first_window ();
      if (window != NULL)
      {
        switch (ev.type)
        {
          case WCTK_EVENT_MOUSE:
            sprintf (evdesc, "Event type: WCTK_EVENT_MOUSE\n"
                             "x:          %d\n"
                             "y:          %d\n"
                             "pressed:    %s\n"
                             "released:   %s\n",
                             ev.mevent.x, ev.mevent.y,
                             (ev.mevent.bstate&BUTTON1_PRESSED)?"true":"false",
                             (ev.mevent.bstate&BUTTON1_RELEASED)?"true":"false");
            break;

          default:
            sprintf (evdesc, "Event type:          %s\n"
                         "Data:                0x%08X\n"
                         "Focused window:      %s\n"
                         "Focused widget type: %s",
                         event_type[ev.type], ev.data, window->title,
                         (window->widget_focus == NULL)?"None":widget_type[window->widget_focus->type-1]);
            break;
        }
        wctk_static_text_set (statictxt, evdesc);
      }
    }
    wctk_draw_rect_fill (0, 0, WCTK_SCREEN_WIDTH+1, WCTK_SCREEN_HEIGHT+1,
        ACS_CKBOARD|COLOR_PAIR(WCTKC_WHITE_DEFAULT));
    wctk_refresh ();
  }

  wctk_window_destroy (window1);
  wctk_window_destroy (window2);
  wctk_window_destroy (window3);
  wctk_quit ();
  return 0;
}

