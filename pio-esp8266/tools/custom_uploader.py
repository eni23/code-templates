import os
from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
esptool_mod = "{0}/tools/esptool-cesanta.py".format(env['PROJECT_DIR'])
env.Replace(UPLOADER=esptool_mod)
env.Replace(UPLOADERFLAGS=[
    '--port',
    '$UPLOAD_PORT',
    'write_flash',
    '--flash_baud=$UPLOAD_SPEED',
    '0'
])
env.Replace(UPLOADCMD='$UPLOADER $UPLOADERFLAGS $SOURCE')
