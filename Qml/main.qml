import QtQuick
import QtQuick.Window


Item {
    width: 640
    height: 480
    visible: true

    Connections{
        target:cppScreenCapture
        property var taskMap:{0:0}
        function onSgOpenNewWindow(father,jsonmsg){
            var json=JSON.parse(jsonmsg)
            var component;
            if(father===null){
                component=itemCompont.createObject(root_father,json)
            }else{
                component=itemCompont.createObject(father,json)
            }

            taskMap[json["objectName"]]=component
        }
        function onSgCloseWindow(name){
            taskMap[name].destroy()
        }
    }

    Component {
        id:itemCompont
        Window{
            id:m_window
            visible:true
        }
    }
}
