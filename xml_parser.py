from yattag import Doc, indent
from pathlib import Path
doc, tag, text = Doc().tagtext()

count_y=0
counter = 0
for count, mesh in enumerate(Path('meshes/stairs').rglob('*.dae')):
    counter += 1
    if counter > 10:
        count_y +=1
        counter = 0
    with tag('model',name="stair_"+str(count)):
        with tag('pose'):
            text(str(10*count % 110) + " " + str(10*count_y) + " 0 0 0 0")
        with tag('static'):
            text('true')
        with tag('link', name="body"):
            with tag('visual', name='visual'):
                with tag('plugin',filename='ignition-gazebo-label-system', name='ignition::gazebo::systems::Label'):
                    with tag('label'):
                        text('5')
                with tag('geometry'):
                    with tag('mesh'):
                        with tag('scale'):
                            scale = 1
                            text(str(scale) + " " + str(scale) + " " + str(scale))
                        with tag('uri'):
                            text(str(mesh))

result = indent(
    doc.getvalue(),
    indentation = ' '*4,
    newline = '\r\n'
)

f = open("demofile2.txt", "w")
f.write(result)
f.close()

