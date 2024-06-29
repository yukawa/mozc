import subprocess
import sys

def main():
  # Delete the self program name (i.e. msvs_rc_wrapper.py).
  sys.argv.pop(0)

  sys.argv.insert(0, "C:/Program Files (x86)/Windows Kits/10/bin/10.0.22621.0/x64/rc.exe")
  # Rest are the options for rc.exe
  try:
    process = subprocess.Popen(sys.argv, stdout=subprocess.PIPE)
  except:
    print('==========')
    print(' ERROR: %s' % ' '.join(sys.argv))
    print('==========')
    raise
  (stdout_content, _) = process.communicate()
  print (stdout_content)
  return process.wait()

if __name__ == '__main__':
  sys.exit(main())


if __name__ == '__main__':
  main()
