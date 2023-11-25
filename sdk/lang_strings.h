/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Standart langpack strings
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef LANGSTRINGS_H
#define LANGSTRINGS_H

// RES_TYPE_STRING
#if !defined(FTR_L7E)
	#define LANG_CLOSE      0x01001CBB // Close
	#define LANG_ADD        0x01000DDC // Add
	#define LANG_PROPERTIES 0x01001CED // Properties
	#define LANG_HIDDEN     0x01001E20 // Hidden
	#define LANG_FILETYPE   0x01001CC2 // File type
	#define LANG_AUDIO      0x01000DAC // Audio
#else
	#define LANG_CLOSE      0x01001D10 // Close
	#define LANG_ADD        0x0100197D // Add
	#define LANG_PROPERTIES 0x01001CD8 // Properties
	#define LANG_HIDDEN     0x01002706 // Hidden
	#define LANG_FILETYPE   0x01001CDF // File type
	#define LANG_AUDIO      0x01000ADE // Audio
#endif

#define LANG_SYNC_WITH_SERVER 0x01000D7E // Sync with server

#define LANG_ERROR            0x010004B8 // Error
#define LANG_COMPLETE         0x01000558 // Complete

#define LANG_EXIT             0x01000A64 // Exit
#define LANG_BACK             0x01001927 // Back
#define LANG_MENU             0x01000BCB // Menu

#define LANG_DELETE           0x01000078 // Delete
#define LANG_DELETE_ALL       0x010001CA // Delete all
#define LANG_COPY             0x010001C4 // Copy
#define LANG_CUT              0x010009E2 // Cut

#define LANG_MOVE             0x01000D59 // Move
#define LANG_RENAME           0x01000877 // Rename
#define LANG_SAVE             0x01000211 // Save
#define LANG_SAVE_AS          0x01000AD8 // Save as
#define LANG_STORED           0x0100052C // Stored
#define LANG_CREATE           0x01000D34 // Create
#define LANG_RUN              0x01001283 // Run
#define LANG_USE              0x01000E0A // Use

#define LANG_SETTINGS         0x01000129 // Settings

#define LANG_BLUETOOTH        0x01000379 // Bluetooth

#define LANG_COPYED           0x010009E5 // Copyed
#define LANG_CUTED            0x010009E6 // Cuted

#define LANG_BEGIN            0x010009F0 // Begin

#define LANG_FILENAME         0x0100086F // File name

#define LANG_MEDIA            0x01000DAD // Media
#define LANG_VIDEO            0x01000DB0 // Video

#define LANG_PLAY             0x010005BE // Play

#define LANG_FILES            0x01001160 // Files
#define LANG_FOLDER           0x01000D43 // Folder

#define LANG_TYPE             0x01000157 // Type
#define LANG_SIZE             0x0100087D // Size
#define LANG_FILE_TYPE        0x01000A48 // File type
#define LANG_FILE_SIZE        0x01000A49 // File size
#define LANG_FILE_LENGTH      0x01000B2A // Length
#define LANG_BITRATE          0x01000DD5 // Bitrate
#define LANG_TYPE2            0x01000B11 // Type
#define LANG_NAME             0x010007B9 // Name

#define LANG_BYTE             0x0100080C // Byte
#define LANG_SECONDS          0x01000122 // Seconds

#define LANG_WAIT             0x01000588 // Wait

#define LANG_PHONEBOOK        0x010000FE // Phonebook
#define LANG_SHORTCUTS        0x0100012C // Shortcuts

#define LANG_VOLUME           0x01000164 // Volume
#define LANG_ABOUT            0x0100049E // About
#define LANG_AUTHOR           0x01000B28 // Author

#define LANG_RECORD           0x010001FB // Record
#define LANG_STOP             0x01000A2B // Stop

#define LANG_NEXT             0x01000A4B // Next

#define LANG_TRANSLATE        0x010006C7 // Translate

#define LANG_CONTACTLIST      0x01001358 // Contact list
#define LANG_CONNECT          0x010000BA // Connect
#define LANG_STATUS           0x0100049F // Status
#define LANG_ADD_CONTACT      0x0100134D // Add contact
#define LANG_DEL_CONTACT      0x0100135E // Delete contact
#define LANG_REN_CONTACT      0x01001B30 // Rename contact
#define LANG_MENU_CONTACTLIST 0x0100135A // Contact list menu

#endif // LANGSTRINGS_H

/* EOF */