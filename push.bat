set d=%date:~0,10%
set t=%time:~0,8%
set timestamp=%d% %t%

git status
git add .
git commit -m "%timestamp% backup from windows"
git push origin CppCTP_API_ypf
echo "Finished Push!"
pause