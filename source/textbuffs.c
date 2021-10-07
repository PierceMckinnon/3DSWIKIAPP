#include "textbuffs.h"
#include "foldcreation.h"
C2D_TextBuf nameBuf;
/*
*This array is for the main page buttons. To add a button add a column to the row. Give it a name
* and a description to be displayed on the screen.
*/
main_struct the_head_array[] =
    {
        {"Getting Started", "Basic setup and usage"},
        {"Reccomended", "Apps and games to improve your experience"},
        {"Architecture", "Overview of 3DS hardware"},
        {"Development", "Create your own homebrew"},
        {"Exploits", "Overview of exploits on latest FW"},
        {"Misc", "Collection of information"},
        {"Resources", "Links and sources to learn more"},
};
/*
*This array is for the sub page buttons. First column is to diplay the information that will be displayed on the button.
*Second column is to attach the button to a parent button from the main page (See the names above to attach).
*Third column is to display the text of the button once clicked. 
*For paragraphs greater then the size of the screen I am toggling the pages by displaying sections of the paragraph at a time
*and the user can use left and right on the key pads to switch between pages.
*Wordwrap from the C2D library will negate spaces beyond 
*those which make the sentence wrap to the next line. This can cause the page number to be greater then the apparent text one screen
*so care to put the appropriate spacing if trying to put a new line. spaces " " are required instead of \n for strlen. IF YOU HAVE MORE 
*THAN ONE PAGE DON'T USE "\n"
*/
sub_struct the_sub_array[] =
    {
        {"Anemone3DS", "Getting Started", "Use this to set custom themese on your 3DS home screen. Go to \"themeplaza.art/themes\" to look for 3DS home screen themes.\n"
                                          "1. In Anemone3DS click R to open the QR Code Scanner and scan the code in Theme Plaza.\n"
                                          "2. Download the theme zip file and place it in the \"Themes\" folder in the root of your "
                                          "SD directory.\n"
                                          "Follow the instructions in Anenome3DS to set a theme. Visit:\n\"github.com/astronautlevel2/Anemone3DS\" for more info."},
        {"Checkpoint", "Getting Started", "Checkpoint is used to backup your save files and overwrite your current saves. Visit:\n\"github.com/FlagBrew/Checkpoint\" for more info."},
        {"Universal-Updater", "Getting Started", "Universal-Updater makes downloading other homebrew applications very easy. It provides a large library of many of the available homebrew applications\n"
                                                 "The list of available homebrew applications can be seen on their website at:\n\"db.universal-team.net/3ds/\".\nVisit:\n\"universal-team.net/projects/universal-updater.ht ml\" for more info."},
        {"GodMode9", "Getting Started", "GodMode9 is a full acess file browser. This gives you access to the files in the FAT partitions in the system NAND and to your SD card."
                                        "It provides the capability to copy, delete, rename files and create folders. There is much more info provided here:\n\"github.com/d0k3/GodMode9\"\nor you can visit the README in GM9 on your 3ds by holding"
                                        " \"START\" on system startup and going to the V drive."},
        {"FBI", "Getting Started", "FBI can be used to install CIA's, manage applications or as a file browser. CIA's can either be installed from your SD card or wirelessly with a URL or QR code. For more information"
                                   "visit:\ngithub.com/Steveice10/FBI for more details."},
        {"Luma3DS", "Getting Started", "github.com/LumaTeam/Luma3DS/wiki"},
        {"Custom-Install", "Reccomended", "Custom-Install allows installation of CIA files directly to SD card from your PC. This drastically reduces installation time."
                                          "Visit:\n\"github.com/ihaveamac/custom-install\" for more info."},
        {"CTGP-7", "Reccomended", "A modpack for Mario Kart 7 adding custom tracks, characters and other features. Adds a lot of depth to the original "
                                  "Mario Kart 7 game and definitely worth the download. Visit:\n\"ctgp-7.github.io\" for more info."},
        {"Overview", "Architecture", "Fill In"},
        {"ARM11", "Architecture", "Fill In"},
        {"ARM9", "Architecture", "Fill In"},
        {"Memory", "Architecture", "Fill In"},
        {"Storage", "Architecture", "Fill In"},
        {"Example", "Development", "Fill In"},
        {"Example", "Exploits", "Fill In"},
        {"Example", "Misc", "Fill In"},
        {"3dbrew", "Resources", "3dbrew is the Wikipedia for the 3DS. Almost all information on any topic related to "
                                "the 3DS can be found there. Link:\n\"3dbrew.org/wiki/Main_Page\""},
        {"Nintendo HB Discord", "Resources", "The Nintendo Homebrew Discord is very helpful for information related to all Nintendo systems. Join this Discord for "
                                             "help with nintendo homebrew development, hacking nintendo consoles or to just chat in general. Visit:\n\"github.com/nh-server\" for a link to the Discord server."},
        {"Talks", "Resources", "\"youtube.com/watch?v=WNUsKx2euFw\"\n\"youtube.com/watch?v=CbFykMLsYsE\""},
        {"Write-up", "Resources", "\"reddit.com/r/3dshacks/comments/6iclr8/a_techni cal_overview_of_the_3ds_operating_system/\""},

};
void createFolders()
{
    nameBuf = C2D_TextBufNew(50);
    for (u8 i = 0; i < ((sizeof(the_head_array)) / sizeof(the_head_array[0])); i++)
    {
        addfolderhead(the_head_array[i].name, the_head_array[i].text);
    }
    for (u8 i = 0; i < ((sizeof(the_sub_array)) / sizeof(the_sub_array[0])); i++)
    {
        addfolder(the_sub_array[i].name, the_sub_array[i].head, the_sub_array[i].text);
    }
}
