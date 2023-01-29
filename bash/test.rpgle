**free

dcl-pr PASE_init pointer extproc;
end-pr;

dcl-pr PASE_execute int(3) extproc;
  instance pointer;
  command pointer value options(*string);
end-pr;

dcl-pr PASE_stdout char(32000) extproc;
  instance pointer;
end-pr;

dcl-pr PASE_stderr char(32000) extproc;
  instance pointer;
end-pr;

dcl-pr PASE_exitcode int(3)extproc;
  instance pointer;
end-pr;

dcl-pr PASE_dispose extproc; //void
  instance pointer;
end-pr;

Dcl-s pasecall pointer;
dcl-s statusCode int(3);
dcl-s output char(50);

pasecall = PASE_init();
PASE_execute(pasecall:'echo "eat my box"');
statusCode = PASE_exitCode(pasecall);

if (statusCode = 0);
	output = PASE_stdout(pasecall);
else;
	output = PASE_stderr(pasecall);
endif;
dsply output;
PASE_dispose(pasecall); //always required

return;