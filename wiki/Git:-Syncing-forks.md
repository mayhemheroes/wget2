### Maintainer: Cloning wget2 repository
This is the official repository.
- git clone git://git.savannah.gnu.org/wget/wget2.git
- cd wget2

### Maintainer: Add remote repositories
Let's assume that there is a fork of the official wget2 repo on Github, e.g. foodev/wget2.
He is an active developers and create commits that we want to integrate on Savannah from time to time.

The maintainer(s) of the official repo on Savannah now add the external repo as 'remote'.
- git remote add foodev https://github.com/foodev/wget2
- git pull --all

List all the branches with
- git branch --all

### Maintainer scenario: foodev sends us a patch generated via 'git format-patch' via email
- Save the patch into a file
- git am <filename> (Todo: How to resolve conflicts)
- Review/Test the changes
- git push
If you want to sync your own Github repo, add it as remote
- git remote add darnir https://github.com/darnir/wget2
- git pull --all
- git push darnir master (if you have a branch master over there, use -f if out of sync)

### Collaborator on Github
Do not make changes to your branch 'master' - this should always reflect the original repo. This makes it easy for you to update your 'master' branch with changes from the 'original/upstream' master branch on Savannah.

Startup procedures:
- git clone https://github.com/darnir/wget2
- git remote add upstream git://git.savannah.gnu.org/wget/wget2.git
- git pull --all

Create an own branch for each 'task' you are working on and make your commits within it.
When done, sync with upstream, rebase/merge and create your patches via format-patch.

Sync your Github repo with upstream:
- git checkout master
- git pull --all
- git merge --ff-only upstream/master
- git push (pushing the new commits from upstream/master to your github master branch)

Sync your 'new-feature' branch before generating patches:
- git checkout new-feature
- git rebase master
- git format-patch -1 (generate patch from last commit to send it via email to bug-wget@gnu.org)
- git push -f (pushing updated tree to your github new-feature branch)
Assume 'new-feature' is a private branch where you can do all the dirty things that you shouldn't on public/shared branches. As soon as your patch has been accepted, remove the branch 'new-feature' locally and from Github.

### For Maintainers Only: Keeping multiple repositories in Sync
For both Wget and Wget2 we have the official repository on the GNU Savannah servers and an unofficial fork on GitHub that is used for firing the Travis tests and other integrations. Hence, it is important that both these repositories remain in sync. For that, please create a new Git remote with multiple push URLs, so that when pushing code, it is automatically pushed to multiple repositories simultaneously.

```
$ git remote add all darnir@git.sv.gnu.org:/srv/git/wget/wget2.git
$ git remote set-url --add --push all git@github.com:darnir/wget2.git
$ git remote set-url --add --push all darnir@git.sv.gnu.org:/srv/git/wget/wget2.git
$ git remote set-url --add --push all git@github.com:rockdaboot/wget2.git
```

This will create a remote called "all" which will push to 3 repositories simultaneously:
- The official savannah repository
- Tim's Repository on GitHub which is used for Travis tests
- Darshit's Repository on GitHub which is his private GitHub fork