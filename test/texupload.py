from glscry import *

test1 = TextureUploadTest("ubyte")

test2 = TextureUploadTest("ub:512x512")
test2.setWidth(512)
test2.setHeight(512)

test3 = TextureUploadTest("byte")
test3.setType(GL_BYTE)

test4 = TextureUploadTest("ushort")
test4.setType(GL_UNSIGNED_SHORT)

test5 = TextureUploadTest("short")
test5.setType(GL_SHORT)

test6 = TextureUploadTest("uint")
test6.setType(GL_UNSIGNED_INT)

test7 = TextureUploadTest("int")
test7.setType(GL_INT)

test8 = TextureUploadTest("float")
test8.setType(GL_FLOAT)

line = runTests('Texture Upload', [test1, test2, test3, test4, test5, test6, test7, test8], 1)
generateGraph('texupload', line, 'ByteRate', xlabel='Texture Format')
