As written in [TheNewRobots.txt](https://www.nccgroup.trust/us/about-us/newsroom-and-events/blog/2019/april/apples_app_site_association_the_new_robots_txt/), Apple introduced a new file `.well-known/apple-app-site-association` with website paths to follow and not to follow. The file is in JSON format - a format that neither wget nor wget2 speak. But here is how to use it with wget/wget2 using a little helper tool called `jq`.

```
wget2 https://www.apple.com/.well-known/apple-app-site-association
wget2 --recursive --base=https://www.apple.com `jq .applinks.details[].paths[] apple-app-site-association | tr -d '"' | tr -d 'NOT '
```

You should use the latest wget2 from git master.