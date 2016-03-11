REPO=cpp_sandbox

echo "# ${REPO}" >> README.md
git init
REPO_GIT=${REPO}.git
git remote add origin https://github.com/rafald/${REPO_GIT}
echo "Create empty rep ${REPO_GIT}"
git remote add origin https://rafald@github.com/rafald/${REPO_GIT}
git push -u origin master
