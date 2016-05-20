cd all/repo3
git checkout vendor
git pull
# get latest vendor 

git checkout –b phantom_merge
git merge –s ours master –m “Phantom merge”
# create “Phantom merge” branch from vendor - s(trategy) is use "ours" branch, ignore "master" branch

git checkout master # switch to master branch
git merge --ff-only phantom_merge # merge/forward only our master branch to phantom_merge
# forward our master to “Phantom merge”

git branch –D phantom_merge
# delete phantom_merge - it was needed only temporarly

git cherry-pick 924989v # etc.
# test
git push origin master:master # TODO ? master:master

