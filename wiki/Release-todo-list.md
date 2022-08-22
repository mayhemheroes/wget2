- Consult [GNU Distributions](https://www.gnu.org/prep/maintain/maintain.html#Distributions)
- Increase/set version numbers (wget2 and libwget) in configure.ac
- Update NEWS
- make distcheck
- tag repo:
```
git commit -a -m "Release Vx.y.z"
git tag -s -m "Release Vx.y.z" wget2-x.y.z
git push --follow-tags
```
   - [ ] Upload triplet to ftp-upload.gnu.org/incoming/ftp or /incoming/alpha
   - [ ] Update on-line manual.

   - [ ] Send announcement to bug-foo@gnu.org
   - [ ] Send announcement to info-gnu@gnu.org
   - [ ] Send announcement to coordinator@translationproject.org
   - [ ] Publish announcement in the savannah news.

   - [ ] Update the FSD entry.
   - [ ] Create release in freecode (freshmeat).
