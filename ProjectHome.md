This project is a port of the very useful **mtree** utility, originally only available in BSD distributions, to Linux and other operating systems.

The **mtree** utility compares the file hierarchy rooted in the current directory against a specification read from the standard input. Messages are written to the standard output for any files whose characteristics do not match the specifications, or which are missing from either the file hierarchy or the specification.

This port of **mtree** uses the `autoconf` infrastructure to maintain portability.

See the ManPages for details.