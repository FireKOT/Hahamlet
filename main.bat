@call parameters.bat main.cpp general.cpp strsort.cpp -o main.exe

@if not errorlevel 1 (
    main.exe %*
)