<div id="top"></div>
<h1 align="center">Perrybotics VEX U Programming</h1>
<br />
<div align="center">

</p>
<img src="images\robotCAD(1).png?" width="500" height="400">
</div>

## Initial testing of the winch and pulley climbing mechanism. 

After programming the general driver controls for the robot, I was testing out the functionality of the robot. As you can see, a pneumatic hook holding the climbing mechanism is released. This then, allows the robot to drive to the horizontal bar. Ultimately allowing the robot to hook onto the bar and climbing up on it. 

<div align="center">
  <video src=https://github.com/user-attachments/assets/479823b1-d0ff-4a1f-93ef-812c9807be44 />
</div>

## Successful test of the autonomous program during the Gear Slingers x CPSWE Open 2024 VEX U Tournament.

For our autonomous programming, I mainly relied on a Intertial Measurement Unit (IMU) and the Integrated Motor Encoders (IME) on the robot. I utilized an odometry algorithm to estimate the position of the robot over time relative to where it initially started at. In conjunction with this, I used a Propertional-Integral-Derivative (PID) controller to ensure that the robot would be able to travel to that position properly. With a properly tuned PID, our robot was able to collect and score many of the game objects (the acorns) into the opposing goal side. 

<div align="center">
  <video src=https://github.com/user-attachments/assets/6f9d7700-0877-4fe4-a05a-1a1c57b0ee22 />
</div>
