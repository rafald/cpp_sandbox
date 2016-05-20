REPO=cpp_sandbox

echo "# ${REPO}" >> README.md
git init
REPO_GIT=${REPO}.git
git remote add origin https://github.com/rafald/${REPO_GIT}
echo "Create empty rep ${REPO_GIT}"
git remote add origin https://rafald@github.com/rafald/${REPO_GIT}
git push -u origin master

# https://chrisjean.com/git-submodules-adding-using-removing-and-updating/
# https://git-scm.com/book/en/v2/Git-Tools-Submodules
# adding submodules
git submodule add https://github.com/RLovelett/eigen.git EIGEN
git status
cat .gitmodules
git submodule init
git submodule update
echo "The submodule repositories added by “git submodule update” are “headless”. This means that they aren’t on a current branch.To fix this, we simply need to switch to a branch. In this example, that would be the master branch. We switch with the following command: “git checkout master“."


# repos on our local server
# git submodule add –b master ../<newRepoName> <newRepoName>
