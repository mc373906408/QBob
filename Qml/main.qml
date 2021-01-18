import QtQuick
import QtQuick.Window


Item {
    width: 0
    height: 0
    visible: false

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
//            flags: Qt.Dialog|Qt.FramelessWindowHint|Qt.WindowCloseButtonHint|Qt.MSWindowsFixedSizeDialogHint
            flags: Qt.Dialog|Qt.FramelessWindowHint|Qt.WindowCloseButtonHint|Qt.WindowStaysOnTopHint
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
