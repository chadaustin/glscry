from glscry import *

runFor = 5

w = 1
h = 1

ul = (5,   5)
ll = (5,   5+h)
lr = (5+w, 5+h)
ur = (5+w, 5)
quad = [ul, ll, lr, ur]

r = (1, 0, 0)
g = (0,0)
b = (0, 0, 1)
w = (1, 1, 1)
rgbw = [r, g, b, w]

ul_tc = (0, 0)
ll_tc = (0, 1)
lr_tc = (1, 1)
ur_tc = (1, 0)
tcs = [ul_tc, ll_tc, lr_tc, ur_tc]

def v(tp): return defineArray(tp, 2, quad)
def c(tp): return defineArray(tp, 3, rgbw)
def n(tp): return defineArray(tp, 3, rgbw)
def t(tp): return defineArray(tp, 2, tcs)

vs = v(Array_s)
vi = v(Array_i)
vf = v(Array_f)
vd = v(Array_d)

cb  = c(Array_b)
cub = c(Array_ub)
cs  = c(Array_s)
cus = c(Array_us)
ci  = c(Array_i)
cui = c(Array_ui)
cf  = c(Array_f)
cd  = c(Array_d)

nb = n(Array_b)
ns = n(Array_s)
ni = n(Array_i)
nf = n(Array_f)
nd = n(Array_d)

ts = t(Array_s)
ti = t(Array_i)
tf = t(Array_f)
td = t(Array_d)

def bg(v=None, c=None, n=None, t=None):
    fmt = (GL_TRIANGLES, 1024)
    return buildGeometry(fmt, v=v, c=c, n=n, t=t)

geos = [
    ("Vs", bg(v=vs)),
    ("Vi", bg(v=vi)),
    ("Vf", bg(v=vf)),
    ("Vd", bg(v=vd)),

    ("Vf_Cb",  bg(vf, c=cb)),
    ("Vf_Cub", bg(vf, c=cub)),
    ("Vf_Cs",  bg(vf, c=cs)),
    ("Vf_Cus", bg(vf, c=cus)),
    ("Vf_Ci",  bg(vf, c=ci)),
    ("Vf_Cui", bg(vf, c=cui)),
    ("Vf_Cf",  bg(vf, c=cf)),
    ("Vf_Cd",  bg(vf, c=cd)),

    ("Vf_Nb", bg(vf, n=nb)),
    ("Vf_Ns", bg(vf, n=ns)),
    ("Vf_Ni", bg(vf, n=ni)),
    ("Vf_Nf", bg(vf, n=nf)),
    ("Vf_Nd", bg(vf, n=nd)),

    ("Vf_Ts", bg(vf, t=ts)),
    ("Vf_Ti", bg(vf, t=ti)),
    ("Vf_Tf", bg(vf, t=tf)),
    ("Vf_Td", bg(vf, t=td)),
]
     

def run(file, test, name):
    tests = [apply(test, g) for g in geos]

    print "Writing data to %s" % file
    line = runTests(name, tests, runFor)
    generateGraph(file + '_vertexrate', line, 'VertexRate')
    generateGraph(file + '_datarate',   line, 'DataRate')
    return line

lines = [
    run('vdatatype_imm', ImmediateTest,           'Immediate'),
    run('vdatatype_dl',  DisplayListTest,         'Display Lists'),
    run('vdatatype_va',  VertexArrayTest,         'Vertex Arrays'),
    run('vdatatype_cva', CompiledVertexArrayTest, 'Compiled Vertex Arrays'),
    run('vdatatype_vbo', VertexBufferObjectTest,  'Vertex Buffers') ]

generateGraph('vdatatype_all_vertexrate', lines, 'VertexRate')
generateGraph('vdatatype_all_datarate',   lines, 'VertexRate')
