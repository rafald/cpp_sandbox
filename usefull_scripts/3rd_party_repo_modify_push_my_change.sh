cd all/repo3
# make changes
git gui # commit as usual
git checkout vendor
git merge –ff-only origin/vendor # update vendor without taking latest updates (we constributed to some historical copy)

thoutgit checkout –b my_change
git cherry-pick 293h39 # contributed commits

git push https://github... my_change:my_change
# Use github to make a pull request.

