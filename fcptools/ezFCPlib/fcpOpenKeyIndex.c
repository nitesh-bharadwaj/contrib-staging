
//
//  This code is part of FreeWeb - an FCP-based client for Freenet
//
//  Designed and implemented by David McNab, david@rebirthing.co.nz
//  CopyLeft (c) 2001 by David McNab
//
//  The FreeWeb website is at http://freeweb.sourceforge.net
//  The website for Freenet is at http://freenet.sourceforge.net
//
//  This code is distributed under the GNU Public Licence (GPL) version 2.
//  See http://www.gnu.org/ for further details of the GPL.
//


#include "ezFCPlib.h"


//
// Function:    fcpOpenKeyIndex()
//
// Arguments:   hfcp
//              name    name of key index to request from
//              date    date to use as base.
//                      NULL for no date
//                      "" or "today" for today's date
//                      "yesterday" for yesterday's date
//                      otherwise, a date string in "YYYYMMDD" format
//
// Returns:     0 if successful
//              -1 if failed
//
// Description: sets up to request keys from an in-freenet key index
//

int fcpOpenKeyIndex(HFCP *hfcp, char *name, char *date, int start)
{
    time_t  time_now = time(NULL);

    // validate name
    if (name == NULL || strlen(name) == 0)
        return -1;
    strcpy(hfcp->keyindex.name, name);

    // validate and initialise date
    if (date == NULL || *date == '\0')
        hfcp->keyindex.basedate[0] = '\0';
    else if (!strcmp(date, "today"))
    {
        //struct tm today;

        //memcpy(&today, gmtime(&time_now), sizeof(struct tm));
        //sprintf(hfcp->keyindex.basedate, "%04d%02d%02d", today.tm_year+1900, today.tm_mon+1, today.tm_mday);
        sprintf(hfcp->keyindex.basedate, "%ld", time_now - (time_now % 86400));
    }
    else if (!strcmp(date, "yesterday"))
    {
        //struct tm yesterday;

        time_now -= 86400;  // go back 24 hours
        //memcpy(&yesterday, gmtime(&time_now), sizeof(struct tm));
        //sprintf(hfcp->keyindex.basedate, "%04d%02d%02d", yesterday.tm_year, yesterday.tm_mon+1, yesterday.tm_mday);
        sprintf(hfcp->keyindex.basedate, "%ld", time_now - (time_now % 86400));
    }
    else if (!strcmp(date, "tomorrow"))
    {
        //struct tm yesterday;

        time_now += 86400;  // go back 24 hours
        //memcpy(&yesterday, gmtime(&time_now), sizeof(struct tm));
        //sprintf(hfcp->keyindex.basedate, "%04d%02d%02d", yesterday.tm_year, yesterday.tm_mon+1, yesterday.tm_mday);
        sprintf(hfcp->keyindex.basedate, "%ld", time_now - (time_now % 86400));
    }
    else
    {
        char *s;

        // validate date string
        for (s = date; *s; s++)
            if (*s < '0' || *s > '9')
                return -1;      // illegal chars in date - spit
        if (s - date != 8)
            return -1;          // date incorrect length - spit

        strcpy(hfcp->keyindex.basedate, date);
    }

    // now set up key number
    if (start < 0)
        start = 0;  // begin at the beginning
    hfcp->keyindex.next_keynum = start;

    return 0;   // success

}       // 'fcpOpenKeyIndex()'
