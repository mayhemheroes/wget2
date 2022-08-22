# Frequently Asked Questions

Most of these questions pertain specifically to Wget2. GNU Wget is now under maintenance mode. That is, we do not plan on adding any new features to it, hence all the development effort has shifted to Wget2 which is a rewrite of Wget.

However, if you have an interesting idea that can greatly enhance Wget, please reach out and let us know. We may still consider it.

## What languages are projects offered in?

GNU Wget / Wget2 is written in C, and hence *all* the projects we offer also require that you write some C code. In the past, we have offered some projects in Python, but since GNU Wget is no longer under active development, there is no need to work on the Python code in there. The test suite for Wget2 is written entirely in C.

## I am (still) interested in GNU Wget. Where do I start?
Welcome to the community! We're happy you want to join us and contribute to a piece of software that most others simply assume *always works*. To start off, you should compile Wget from source and run all the tests successfully. In case you're stuck, it is because:

1. You've not read the provided documentation thoroughly. Please go back and read it once more.
2. The provided documentation isn't good enough. Reach out to us via an email/IRC. Also, submit a patch for extra brownie points.
3. You're on a weird or unsupported platform. In this case, you can take a full GSoC project porting Wget2 to the platform you're running on.

Also, take a look at this rough [starting guide](https://gitlab.com/gnuwget/wget2/wikis/Contributing-guide-for-new-developers) written by a previous student (now a regular contributor), Avinash Sonawane. Any improvements there will be appreciated.

## Right, I've managed to compile Wget and it passes all tests. Now what?
Congratulations! You've passed an important barrier to working on GNU Wget2. You'd be surprised how many others have tried and failed at the earlier step. Now, you should get your hands dirty. Dive into the Wget2 source and try to fix some open bugs. You can find a list of open bugs on the [Wget2 Issue List](https://gitlab.com/gnuwget/wget2/issues). You may also work on bugs in GNU Wget, those can be found on the [Savannah Bugtracker](https://savannah.gnu.org/bugs/?group=wget).

## I don't know what bugs to work on. Can you please give me a list of tasks?
Ideally, you should try to close as many bugs on the list as possible. Not all bug reports are valid either. Oftentimes people complain about the behavior of Wget when the fault lies with a badly programmed web server. For Wget2, take a look at the bugs labelled [Junior/Starter](https://gitlab.com/gnuwget/wget2/issues?label_name%5B%5D=Junior+%2F+Starter), these are meant to be easy to fix issues which can be useful for someone getting used to the Wget2 codebase. Similarly, here is a set of simple bugs for Wget (In my humble opinion) that you could probably work on closing:

3. [43669](https://savannah.gnu.org/bugs/?43669): Valid for Wget2 too
4. [41003](https://savannah.gnu.org/bugs/?41003)
5. [41002](https://savannah.gnu.org/bugs/?41002)
6. [39175](https://savannah.gnu.org/bugs/?39175): Check for validity with Wget2 too
8. [40583](https://savannah.gnu.org/bugs/?40583)
9. [52356](https://savannah.gnu.org/bugs/?52356)
10. [44516](https://savannah.gnu.org/bugs/?44516): May be valid with Wget2 too

Please remember to also write a test case to show that the bug no longer exists.

There are lots of other open bugs and you're welcome to work on any of them. Just let us know if you're working on something so that there is no duplication of effort.

## What is the best way to contact the mentors?

There are currently three (potential) mentors for GNU Wget2

* [Tim Ruehsen](mailto:tim.ruehsen@gmx.de)
* [Darshit Shah](mailto:darnir@gnu.org)
* [Ander Juaristi](mailto:ajuaristi@gmx.es)

We will split the mentoring load amongst ourselves based on the number of slots we get this year. If you have any queries or need help with your application for GSoC please do not hesitate to contact us directly. However, please remember to CC each of the mentors in all your emails so that everyone remains on the same page.

If you are interested in a technical discussion, want some code review or wish to submit a patch to Wget(Woohoo!), please direct the email towards our mailing list at <wget-dev@gnu.org>. This way the rest of the community gets to pitch in on any technical discussions and we identify design / implementation flaws a [lot faster](http://en.wikipedia.org/wiki/Linus%27s_Law). For Wget2, you may open a new Merge Request to submit code.

You may also ping us on IRC. Giuseppe(gscrivano) and Darshit(darnir) maintain a near 24x7 presence on IRC. If you need any help please ping us on #wget and we'll get back to you as soon as we can. You can also connect to the channel via Matrix.

Remember, GNU Wget is developed entirely through volunteer effort. Most of the developers have other day jobs and hacking on Wget is only a hobby. As a result, you may not always get an answer to your mails immediately. Please allow for atleast 48 hours to go without an answer before you try pinging anyone about it. The same goes for IRC. Even though we're online on IRC, it doesn't mean we're active on it. Responses can take time especially on working days as most of the mentors are busy with their regular jobs.

## Where are the Wget Sources located?
Unlike a lot of the newer projects, Wget's development is **not** done on GitHub. Instead Wget sources are hosted on the Savannah servers at <http://git.savannah.gnu.org/cgit/wget.git>

The development of Wget2 however takes place here on GitLab. You can access the main Wget2 repository [here](https://gitlab.com/gnuwget/wget2).

## What are the various projects being offered for GSoC by GNU Wget?
We have a bunch of ideas that we have documented on the [GNU GSoC](http://www.gnu.org/software/soc-projects/ideas.html#wget) page. We're also working on adding more information about these projects on this wiki. Visit the ideas page for the current year on the wiki for an updated list of projects being offered this year

Apart from the ones that we have suggested, we also encourage you to come up with your own ideas. 

## How do I improve my chances of getting selected for GSoC?
The absolute most important part of your application for GSoC is the proposal that you submit. Spend as much time as you can working on writing a spectacular proposal. It should display a good understanding of the problem, your thought process for solving it, expected roadblocks and most importantly a timeline. However, a proposal alone does not a GSoC application make. We value people who we think will eventually join our community for a longer term and not disappear at the end of the program. Remember, worse than having a project not implemented is someone finishing it and disappearing; because now **we** need to maintain that codebase.

Ideally, you should also have atleast one commit merged into our code base or in the pipeline when you submit your proposal. This is a basic test that shows that you are capable of compiling the source, reading and understanding it and writing some code to fix a known problem. All very important traits.

Remember to choose your project of interest early on and make some strides in that direction. While you are allowed to submit multiple proposals for different projects to the same organization, it is not advised. Writing a proposal is a massive task that will take a lot of your time. Hence, you should rather concentrate on a single extremely good proposal about a project you're keen to work on rather than having three okay proposals about projects that you don't mind working on.

## I have little or no experience in C. Should I even bother applying?
The answer to this question is a very emphatic **YES!**. Please apply! Google Summer of Code is a program where we try to get fresh programmers with little or no experience involved in the world of open source. The mentors are very well aware of this and we are willing to hold your hand, teaching you about the absolute basic steps if required. Only thing we ask for? Read, when given some material.

More experience does not automatically improve your chances of getting selected either. Think of this as a job interview. The most qualified person does not always get selected, but the one who best fits the team does. We expect you to learn something new when you join us for a GSoC project. For more information, take a look at this page in the Student's Guide, [Am I Good Enough?](http://write.flossmanuals.net/gsocstudentguide/am-i-good-enough/). In fact we recommend that you go through the full guide, it will help you understand the GSoC program a lot better.

## I have exams during the coding period / I have university project assignments / I'm going on a vacation for n days during the coding period. Can I still apply?

Once again, the answer is an emphatic **YES!**. However, with one caveat, you need to inform us about these potential time periods where you may not be productive. And you should account for them in your timeline when you draft your proposal. So long as you've informed us about potential periods where you may not be able to produce any meaningful work because of other commitments (This includes a vacation to Hawaii too), it's okay. Really. Of course, if its going to be a slightly extended period, we'll ask you to compensate for it by starting earlier / working a bit harder during the other times / anything else through mutual consent. 
