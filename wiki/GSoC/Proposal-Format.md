# Google Summer of Code Student Proposals Format

GNU Wget participates in Google Summer of Code under the umbrella of the [GNU Project](http://www.google-melange.com/gsoc/org2/google/gsoc2015/gnu). Hence, when submitting your proposal, it is important that you follow the [GNU Student Proposals Guidelines](http://www.gnu.org/software/soc-projects/guidelines.html).

For your reference on what constitutes a good proposal, the following is the one that was selected in one of the previous years:

***

> **Short description**: At the end of the project, the following objectives should be met: Metalink support is completely implemented and functional; concurrent downloads in recursive mode is complete and functional; simultaneous downloads through a mirror list; concurrent downloads of multiple files.

### Your name

XXXX XXXX

### Your email address

XXX@XXXX.XXX

### IRC

XXXXXX

### The name of the project

[GNU Wget] Extend concurrency support in Wget

### Summary

Project suggestion states that at the end of the project, the following objectives should be met:

- Metalink support is completely implemented and functional.

- Concurrent downloads in recursive mode is complete and functional.

- Simultaneous downloads through a mirror list.

- Concurrent downloads of multiple files.

### Benefits

Users will be able to concurrently download multiple files from multiple files or download one file from multiple servers. They will be able to specify Metalink file to download files.

### Deliverables

Some Metalink code will be completely rewritten, most of it will be improved in order to comply with specifications.

Code for concurrent download of a single file through mirror-list and concurrent download of multiple files from multiple servers will be added. Race conditions will be fixed in retrieve_tree() function.

Documentation will be updated with new features.

### Plan

#### Metalink reimplementation

Current implementation of Metalink supports only specific format (version 3.0) of Metalink. It does it partially, for example:

- it doesn't account for the absence of some arguments (they might be optional) resulting in crash,

- priority of available resources is not taken into account - it uses the first one listed,

- hash pieces used for checking correctness of download are completely ignored.

Some entities use newer Metalink 4.0 standard for distribution. Metalink 3.0 and 4.0 are not compatible. While the parsing for both are done by the library libmetalink, which provides the same abstraction for both, some details may vary. One might expect some attribute to be present in 4.0 abstraction, since it's present in 3.0, but that's not the case.

One objective of this project is to reimplement Metalink 3.0 standard and extend it with Metalink 4.0 standard.  Metalink 3.0 will be written with respect to its specification found on http://www.metalinker.org/Metalink_3.0_Spec.txt. Metalink 4.0 will be written with respect to RFC 5854 and RFC 6249 documents.

Second part of the project will implement feature for concurrent download of multiple files. Metalink file can also include multiple files. Feature for downloading them concurrently will also be added.

#### Extend concurrency support

1. Concurrent downloads in recursive mode

Current implementation of concurrent downloads in recursive mode still has some race conditions. An inspection of code shows the source of race conditions is mostly connected to writing to a logfile. Objective here is to find all of them and fix them.

2. Downloading one file through a mirror-list

The implementation of this should be straightforward with the function retrieve_url() already having support for defining segment length. The basic idea is to split into N segments, where N is number of threads. Every thread downloads its own segment from a different server. A server might become unavailable during downloading. For this purpose we keep track of available mirror servers. When a thread exceeds the number of retries, it switches to another server and continues download.

3. Downloading multiple files from multiple servers

Since files are independent from each other, retrieve_url() can be used separately on every file. Each file be downloaded in a separate thread. In case where there are more files than threads, files will be dynamically allocated to available threads using URL queue already implemented in Wget. I.e. when one thread finishes downloading its file, url_dequeue() will be made and another file will be allocated to a now finished thread.

Since a support for concurrent download of a single file will be added beforehand, a possibility where individual file might be downloaded through multiple servers arises. To ensure a user has a maximum control, I suggest having a simple format:

"-G <number_of_files> -Y <number of mirrors for first file> <mirror list for first file> <additional parameters for first file> -Y <number of mirrors for second file> ... -Y"

-G parameter starts environment for multiple files, -Y is a delimiter between files. Having such format allows user to select its own parameter for each file. 

A similar file format to Metalink format could also be introduced. These are just suggestions and are debatable.

### Timeline

Before 19 May: read all about Metalink 3.0/4.0 standard, HTTP standard and get used to git. A design document should be discussed with mentor and fine tune the details with community.

19 May - 1 June: Start working on concurrent backend single file download.  At the end user will be able to download file with some hacks. I still have college duties in this interval so my work hours might be suboptimal.

2 June - 8 June: Create frontend for concurrent single file download. Make sure all the switches do the right clicks in backend.

9 June - 15 June: Fix race conditions with recursive mode.

16 June - 22 June: Break for exams.

23 June - 13 July: Work on backend code for concurrent download of multiple files from multiple servers. Add possibility to download every single file with multiple threads.

14 July - 20 July:  Create frontend for concurrent download of multiple files from multiple servers.

21 July - 3 August: Reimplement current Metalink code to comply with Metalink 3.0 specification. Distinguish (where needed) between Metalink 3.0 and Metalink 4.0, and implement Metalink 4.0 support.

4 August - 17 August: Prepare code for merging and make sure documentation is flawless.

#### Mid-term evaluation

At this point concurrent download of a single file through a mirror-list should be up and working. I'm not completely sure if fixing race conditions in recursive mode will be done by this time, since race conditions can be pesky,

Code will be tested with different number of threads and files to see if it works. I will look into possibility to disconnect a mirror server to see if a thread will properly switch to another mirror server.

### Communication

I will communicate with mentor through email and IRC. I'll talk to him at least once a week. When I complete a self-contained pack of features, I'll be sure to upload patch to mailing list. I will listen to feedback and be sure to follow advices.

### Qualification

I'm familiar with pthreads, OpenMP, CUDA, OpenCL, MPI. I understand and able to apply various concepts in distributed systems and I'm used to work in multi-threaded environments. I'm advanced user of C and I know do's and don'ts. I did some minor projects with it (compression tool, small operating system) and used it with technologies listed above. I've never used git before (except for checkouts) so my goal is to learn at least most useful commands.

Because I like C and distributed systems in general, this project was a natural pick. I haven't worked on any Free Software before and I look forward to this to be a breakthrough.

***
