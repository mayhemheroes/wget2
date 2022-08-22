Whenever you see `pipeline #123... failed ...` and you don't know what to do:

- Don't ask anyone before you didn't perform the following steps (ideally, don't even push before `make && make check && make check-valgrind` didn't succeed locally).
- Click on the pipeline number `#123...` to see a list of the CI runners and their status.
- Click on one of the red (failed) ones.
- You now see a scrollable window with all the console messages. Scroll up and look for the problem. If it's clear to you (e.g. compilation failed), fix it.

If it's a failed test, you want to take a look into the log file of this test:
- Click on `browse` on the right side of the page.
- Navigate to the log file you want to view.
- Click on the log file name to download and view it.
- Reproduce the problem locally, fix the bug and commit/push again.

If you can't reproduce it locally or if it's not solvable for you, ask the Wget2 community using a comment in your Merge Request.
