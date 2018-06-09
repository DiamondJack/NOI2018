@echo off
for /l %%i in (3,3,6) do (
std < %%i.in > %%i.ans
)
pause