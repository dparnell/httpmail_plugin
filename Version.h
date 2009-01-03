/*
 *  Version.h
 *  httpmail
 *
 *  Created by Daniel Parnell on Sun Feb 09 2003.
 *  Copyright (c) 2003 Daniel Parnell. All rights reserved.
 * 
 */

#define VERSION_NUMBER 1.53

#ifdef TARGET_JAGUAR
#define VERSION_TARGET @"Jaguar"
#endif

#ifdef TARGET_PANTHER
#define VERSION_TARGET @"Panther"
#endif

#ifdef TARGET_TIGER
#define VERSION_TARGET @"Tiger"
#endif

#ifdef TARGET_LEOPARD
#define VERSION_TARGET @"Leopard"
#endif