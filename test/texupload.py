from glscry import *

def pad(s, n):
    return s + ' ' * (n - len(s))

def name(s):
    return pad(s, 20)

test1 = TextureUploadTest(name("unsigned_byte"))

test2 = TextureUploadTest(name("ub:512x512"))
test2.setWidth(512)
test2.setHeight(512)

test3 = TextureUploadTest(name("byte"))
test3.setType(GL_BYTE)

test4 = TextureUploadTest(name("unsigned_short"))
test4.setType(GL_UNSIGNED_SHORT)

test5 = TextureUploadTest(name("short"))
test5.setType(GL_SHORT)

test6 = TextureUploadTest(name("unsigned_int"))
test6.setType(GL_UNSIGNED_INT)

test7 = TextureUploadTest(name("int"))
test7.setType(GL_INT)

test8 = TextureUploadTest(name("float"))
test8.setType(GL_FLOAT)

runTests("upload.data",
         [test1, test2, test3, test4, test5, test6, test7, test8],
         1,
         "ByteRate")
