import QtQuick
import QtQuick.Window


Item {
    width: 300
    height: 300
    visible: true

    /*动态加载window*/
    Connections{
        target:cppScreenCapture
        property var taskMap:{0:0}
        function onSgOpenWindow(parent,jsonmsg){
            var json=JSON.parse(jsonmsg)
            taskMap[json["objectName"]]=itemCompont.createObject(parent,json)
        }
        function onSgCloseWindow(objectName){
            taskMap[objectName].destroy()
        }
    }

    Component {
        id:itemCompont
        Window{
            id:m_window
            visible:true
            Image {
                id: img
                anchors.fill: parent
            }
            Connections{
                target: cppScreenCapture
                function onSgRefeshPixmap(){
                    img.source=""
                    img.source="image://screenshot"
                }
            }
        }
    }
}
