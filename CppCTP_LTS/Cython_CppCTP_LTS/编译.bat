@echo off
:begin
echo ***********************
echo *ȷ�ϱ���? y or n
set input=
set /p input=*
if %input% == y (
	python setup.py build_ext --inplace
	echo ***********************
	echo.
	goto begin
) else (
	if %input% == n (
		echo ***********************
		echo "��������˳�"
		pause
	) else (
		echo ***********************
		echo "�������!��������"
		pause
	)
)