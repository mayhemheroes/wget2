# Continuous Integration for Wget2

We would like to have constant tests for Wget2 to ensure that no regressions creep in. For this, tests must be performed on a variety of platforms and with multiple configurations. Currently, there exists no one-stop solution to all our continuous integration requirements. The following is a summary of what configurations are tested and where the tests are done.

| Platform         | Continuous Integration Service   | Status              | Notes          |
| -----------      | -------------------------------- | --------            | -------        |
| Linux            | GitLab Pipelines                 | In Progress         |                |
| OSX              | GitLab Pipelines                 | Not started         | Must read docs |
| Windows - Native | AppVeyor                         | Not Started         |                |
| Windows - MingW  | GitLab Pipelines                 | Not Started         | Read Docs      |
| BSD              | N/a                              | Not Started         |                |
| Solaris          | Dagobert's Build Farm            | Running from GitHub | Move to Gitlab |


