# Keyestudio-Turtle-Robot-component-testing

### **Tested (working) :** 

<ul>
  <li>Drive Motors (both)</li>
  <li>Ultrasonic servo</li>
  <li>Ultrasonic sensor</li>
  <li>Matrix</li>
  <li>Line following module</li>
  <li>Bluetooth Module (HM-10)</li>
</ul>

>Note on Bluetooth : I am using an application called ``BLE Device Info`` on MacOS to transmit and receive serial messages to/from the robot. For MacOs this application works and does its job but you'd need to use something else on a different platform.

### Update :

All components have now been tested (save for IR receiver which I do not plan to test for now). At the moment the robot is able to respond to simple characters sent over serial using the BT module and respond with a string sent through serial again. All other sensors and components are working as well in ``componentTests.ino``. The next step is to start a couple of more complicated projects using all components to their full potential (such as making the robot bluetooth controlled).