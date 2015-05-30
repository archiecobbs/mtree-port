Man page for mtree(8):
```
MTREE(8)                             BSD System Manager's Manual                            MTREE(8)

NAME
     mtree -- map a directory hierarchy

SYNOPSIS
     mtree [-LPUcdeinqruxw] [-f spec] [-I include-list] [-K keywords] [-k keywords] [-p path]
           [-s seed] [-X exclude-list]

DESCRIPTION
     The mtree utility compares the file hierarchy rooted in the current directory against a speci-
     fication read from the standard input.  Messages are written to the standard output for any
     files whose characteristics do not match the specifications, or which are missing from either
     the file hierarchy or the specification.

     The options are as follows:

     -L    Follow all symbolic links in the file hierarchy.

     -P    Do not follow symbolic links in the file hierarchy, instead consider the symbolic link
           itself in any comparisons.  This is the default.

     -U    Modify the owner, group, permissions, and modification time of existing files to match
           the specification and create any missing directories or symbolic links.  User, group and
           permissions must all be specified for missing directories to be created.  Corrected mis-
           matches are not considered errors.

     -c    Print a specification for the file hierarchy to the standard output.

     -d    Ignore everything except directory type files.

     -e    Do not complain about files that are in the file hierarchy, but not in the specification.

     -i    Indent the output 4 spaces each time a directory level is descended when creating a spec-
           ification with the -c option.  This does not affect either the /set statements or the
           comment before each directory.  It does however affect the comment before the close of
           each directory.

     -n    Do not emit pathname comments when creating a specification.  Normally a comment is emit-
           ted before each directory and before the close of that directory when using the -c
           option.

     -q    Quiet mode.  Do not complain when a ``missing'' directory cannot be created because it
           already exists.  This occurs when the directory is a symbolic link.

     -r    Remove any files in the file hierarchy that are not described in the specification.

     -u    Same as -U except a status of 2 is returned if the file hierarchy did not match the spec-
           ification.

     -w    Make some errors non-fatal warnings.

     -x    Do not descend below mount points in the file hierarchy.

     -f file
           Read the specification from file, instead of from the standard input.

           If this option is specified twice, the two specifications are compared to each other
           rather than to the file hierarchy.  The specifications will be sorted like output gener-
           ated using -c.  The output format in this case is somewhat remniscent of comm(1), having
           "in first spec only", "in second spec only", and "different" columns, prefixed by zero,
           one and two TAB characters respectively.  Each entry in the "different" column occupies
           two lines, one from each specification.

     -I include-list
           The specified file contains fnmatch(3) patterns matching files to be included in the
           specification, one to a line.  If the pattern contains a `/' character, it will be
           matched against entire pathnames (relative to the starting directory); otherwise, it will
           be matched against basenames only.  No comments are allowed in the include-list file.

           If this flag is not present, all files are included by default.

     -K keywords
           Add the specified (whitespace or comma separated) keywords to the current set of key-
           words.

     -k keywords
           Use the ``type'' keyword plus the specified (whitespace or comma separated) keywords
           instead of the current set of keywords.

     -p path
           Use the file hierarchy rooted in path, instead of the current directory.

     -s seed
           Display a single checksum to the standard error output that represents all of the files
           for which the keyword cksum was specified.  The checksum is seeded with the specified
           value.

     -X exclude-list
           The specified file contains fnmatch(3) patterns matching files to be excluded from the
           specification, one to a line.  If the pattern contains a `/' character, it will be
           matched against entire pathnames (relative to the starting directory); otherwise, it will
           be matched against basenames only.  No comments are allowed in the exclude-list file.

           If both -I and -X are specified, any files matching both lists are excluded.

     Specifications are mostly composed of ``keywords'', i.e., strings that specify values relating
     to files.  No keywords have default values, and if a keyword has no value set, no checks based
     on it are performed.

     Currently supported keywords are as follows:

     cksum       The checksum of the file using the default algorithm specified by the cksum(1)
                 utility.

     flags       The file flags as a symbolic name.  See chflags(1) for information on these names.
                 If no flags are to be set the string ``none'' may be used to override the current
                 default.

     ignore      Ignore any file hierarchy below this file.

     gid         The file group as a numeric value.

     gname       The file group as a symbolic name.

     md5digest   The MD5 message digest of the file.

     sha1digest  The FIPS 160-1 (``SHA-1'') message digest of the file.

     sha256digest
                 The FIPS 180-2 (``SHA-256'') message digest of the file.

     ripemd160digest
                 The RIPEMD160 message digest of the file.

     mode        The current file's permissions as a numeric (octal) or symbolic value.

     nlink       The number of hard links the file is expected to have.

     nochange    Make sure this file or directory exists but otherwise ignore all attributes.

     optional    The file is optional; do not complain about the file if it is not in the file hier-
                 archy.

     uid         The file owner as a numeric value.

     uname       The file owner as a symbolic name.

     size        The size, in bytes, of the file.

     link        The file the symbolic link is expected to reference.

     time        The last modification time of the file, in seconds and nanoseconds.  The value
                 should include a period character and exactly nine digits after the period.

     type        The type of the file; may be set to any one of the following:

                 block       block special device
                 char        character special device
                 dir         directory
                 fifo        fifo
                 file        regular file
                 link        symbolic link
                 socket      socket

     The default set of keywords are flags, gid, mode, nlink, size, link, time, and uid.

     There are four types of lines in a specification.

     The first type of line sets a global value for a keyword, and consists of the string ``/set''
     followed by whitespace, followed by sets of keyword/value pairs, separated by whitespace.  Key-
     word/value pairs consist of a keyword, followed by an equals sign (``=''), followed by a value,
     without whitespace characters.  Once a keyword has been set, its value remains unchanged until
     either reset or unset.

     The second type of line unsets keywords and consists of the string ``/unset'', followed by
     whitespace, followed by one or more keywords, separated by whitespace.

     The third type of line is a file specification and consists of a file name, followed by white-
     space, followed by zero or more whitespace separated keyword/value pairs.  The file name may be
     preceded by whitespace characters.  The file name may contain any of the standard file name
     matching characters (``['', ``]'', ``?'' or ``*''), in which case files in the hierarchy will
     be associated with the first pattern that they match.

     Each of the keyword/value pairs consist of a keyword, followed by an equals sign (``=''), fol-
     lowed by the keyword's value, without whitespace characters.  These values override, without
     changing, the global value of the corresponding keyword.

     All paths are relative.  Specifying a directory will cause subsequent files to be searched for
     in that directory hierarchy.  Which brings us to the last type of line in a specification: a
     line containing only the string ``..'' causes the current directory path to ascend one level.

     Empty lines and lines whose first non-whitespace character is a hash mark (``#'') are ignored.

     The mtree utility exits with a status of 0 on success, 1 if any error occurred, and 2 if the
     file hierarchy did not match the specification.  A status of 2 is converted to a status of 0 if
     the -U option is used.

FILES
     /etc/mtree  system specification directory

EXIT STATUS
     The mtree utility exits 0 on success, and >0 if an error occurs.

EXAMPLES
     To detect system binaries that have been ``trojan horsed'', it is recommended that mtree -K
     sha256digest be run on the file systems, and a copy of the results stored on a different
     machine, or, at least, in encrypted form.  The output file itself should be digested using the
     sha256(1) utility.  Then, periodically, mtree and sha256(1) should be run against the on-line
     specifications.  While it is possible for the bad guys to change the on-line specifications to
     conform to their modified binaries, it is believed to be impractical for them to create a modi-
     fied specification which has the same SHA-256 digest as the original.

     The -d and -u options can be used in combination to create directory hierarchies for distribu-
     tions and other such things; the files in /etc/mtree were used to create almost all directories
     in this FreeBSD distribution.

     To create an /etc/mtree style BSD.*.dist file, use mtree -c -d -i -n -k
     uname,gname,mode,nochange.

SEE ALSO
     chflags(1), chgrp(1), chmod(1), cksum(1), md5(1), stat(2), fts(3), md5(3), chown(8)

     mtree-port: Utility for creating and verifying file hierarchies, http://mtree-
     port.googlecode.com/.

HISTORY
     The mtree utility appeared in 4.3BSD-Reno.  The MD5 digest capability was added in FreeBSD 2.1,
     in response to the widespread use of programs which can spoof cksum(1).  The SHA-1 and
     RIPEMD160 digests were added in FreeBSD 4.0, as new attacks have demonstrated weaknesses in
     MD5.  The SHA-256 digest was added in FreeBSD 6.0.  Support for file flags was added in
     FreeBSD 4.0, and mostly comes from NetBSD.

     mtree was ported to Linux by Archie L. Cobbs <archie@dellroad.org>

BSD                                         June 16, 2007                                        BSD
```
Man page for mtree(5):
```
MTREE(5)                               BSD File Formats Manual                              MTREE(5)

NAME
     mtree -- format of mtree dir hierarchy files

DESCRIPTION
     The mtree format is a textual format that describes a collection of filesystem objects.  Such
     files are typically used to create or verify directory hierarchies.

   General Format
     An mtree file consists of a series of lines, each providing information about a single filesys-
     tem object.  Leading whitespace is always ignored.

     When encoding file or pathnames, any backslash character or character outside of the 95 print-
     able ASCII characters must be encoded as a a backslash followed by three octal digits.  When
     reading mtree files, any appearance of a backslash followed by three octal digits should be
     converted into the corresponding character.

     Each line is interpreted independently as one of the following types:

     Signature   The first line of any mtree file must begin with ``#mtree''.  If a file contains
                 any full path entries, the first line should begin with ``#mtree v2.0'', otherwise,
                 the first line should begin with ``#mtree v1.0''.

     Blank       Blank lines are ignored.

     Comment     Lines beginning with # are ignored.

     Special     Lines beginning with / are special commands that influence the interpretation of
                 later lines.

     Relative    If the first whitespace-delimited word has no / characters, it is the name of a
                 file in the current directory.  Any relative entry that describes a directory
                 changes the current directory.

     dot-dot     As a special case, a relative entry with the filename .. changes the current direc-
                 tory to the parent directory.  Options on dot-dot entries are always ignored.

     Full        If the first whitespace-delimited word has a / character after the first character,
                 it is the pathname of a file relative to the starting directory.  There can be mul-
                 tiple full entries describing the same file.

     Some tools that process mtree files may require that multiple lines describing the same file
     occur consecutively.  It is not permitted for the same file to be mentioned using both a rela-
     tive and a full file specification.

   Special commands
     Two special commands are currently defined:

     /set        This command defines default values for one or more keywords.  It is followed on
                 the same line by one or more whitespace-separated keyword definitions.  These defi-
                 nitions apply to all following files that do not specify a value for that keyword.

     /unset      This command removes any default value set by a previous /set command.  It is fol-
                 lowed on the same line by one or more keywords separated by whitespace.

   Keywords
     After the filename, a full or relative entry consists of zero or more whitespace-separated key-
     word definitions.  Each such definitions consists of a key from the following list immediately
     followed by an '=' sign and a value.  Software programs reading mtree files should warn about
     unrecognized keywords.

     Currently supported keywords are as follows:

     cksum       The checksum of the file using the default algorithm specified by the cksum(1)
                 utility.

     contents    The full pathname of a file whose contents should be compared to the contents of
                 this file.

     flags       The file flags as a symbolic name.  See chflags(1) for information on these names.
                 If no flags are to be set the string ``none'' may be used to override the current
                 default.

     ignore      Ignore any file hierarchy below this file.

     gid         The file group as a numeric value.

     gname       The file group as a symbolic name.

     md5         The MD5 message digest of the file.

     md5digest   A synonym for md5.

     sha1        The FIPS 160-1 (``SHA-1'') message digest of the file.

     sha1digest  A synonym for sha1.

     sha256      The FIPS 180-2 (``SHA-256'') message digest of the file.

     sha256digest
                 A synonym for sha256.

     ripemd160digest
                 The RIPEMD160 message digest of the file.

     rmd160      A synonym for ripemd160digest.

     rmd160digest
                 A synonym for ripemd160digest.

     mode        The current file's permissions as a numeric (octal) or symbolic value.

     nlink       The number of hard links the file is expected to have.

     nochange    Make sure this file or directory exists but otherwise ignore all attributes.

     uid         The file owner as a numeric value.

     uname       The file owner as a symbolic name.

     size        The size, in bytes, of the file.

     link        The file the symbolic link is expected to reference.

     time        The last modification time of the file, in seconds and nanoseconds.  The value
                 should include a period character and exactly nine digits after the period.

     type        The type of the file; may be set to any one of the following:

                 block       block special device
                 char        character special device
                 dir         directory
                 fifo        fifo
                 file        regular file
                 link        symbolic link
                 socket      socket

SEE ALSO
     cksum(1), find(1), mtree(8)

     mtree-port: Utility for creating and verifying file hierarchies, http://mtree-
     port.googlecode.com/.

BUGS
     The FreeBSD implementation of mtree does not currently support the mtree 2.0 format.  The
     requirement for a ``#mtree'' signature line is new and not yet widely implemented.

HISTORY
     The mtree utility appeared in 4.3BSD-Reno.  The MD5 digest capability was added in FreeBSD 2.1,
     in response to the widespread use of programs which can spoof cksum(1).  The SHA-1 and
     RIPEMD160 digests were added in FreeBSD 4.0, as new attacks have demonstrated weaknesses in
     MD5.  The SHA-256 digest was added in FreeBSD 6.0.  Support for file flags was added in
     FreeBSD 4.0, and mostly comes from NetBSD.  The ``full'' entry format was added by NetBSD.

     mtree was ported to Linux by Archie L. Cobbs <archie@dellroad.org>

BSD                                       December 31, 2007                                      BSD
```