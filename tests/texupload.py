from triagara import *

test1 = TextureUploadTest()

test2 = TextureUploadTest()
test2.setWidth(512)
test2.setHeight(512)

test3 = TextureUploadTest()
test3.setType(GL_BYTE)

test4 = TextureUploadTest()
test4.setType(GL_UNSIGNED_SHORT)

test5 = TextureUploadTest()
test5.setType(GL_SHORT)

test6 = TextureUploadTest()
test6.setType(GL_UNSIGNED_INT)

test7 = TextureUploadTest()
test7.setType(GL_INT)

test8 = TextureUploadTest()
test8.setType(GL_FLOAT)

runTests("upload.data",
         [test1, test2, test3, test4, test5, test6, test7, test8],
         1,
         "PixelRate")
