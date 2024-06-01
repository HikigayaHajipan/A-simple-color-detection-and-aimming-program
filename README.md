# 2024华南理工大学机甲杯校内赛视觉开源代码
本代码是24年华南虎举办的机甲杯校内赛中华南虤队的色块识别与瞄准程序，希望能给想要了解或者学习的同学们提供一点参考和帮助。
由于个人水平实在有限，代码也十分粗浅，如有纰漏还请多多包涵......（哭
也欢迎各位一起交流和讨论，联系方式：QQ：235652879
<!-- TOC -->

- [2024华南理工大学机甲杯校内赛视觉开源代码](#2024华南理工大学机甲杯校内赛视觉开源代码)
  - [1.代码主要逻辑介绍和效果展示](#1.代码主要逻辑介绍和效果展示)
  - [2. 依赖工具和编译环境](#2-依赖工具和编译环境)
  - [3.杂谈](#3.杂谈)
  - [4. 功能模块具体实现方案](#4-功能模块具体实现方案)
    - [装甲检测：](#装甲检测)
    - [陀螺检测：](#陀螺检测)
    - [移动预测：](#移动预测)
    - [大符识别：](#大符识别)
    - [大符击打：](#大符击打)
  - [5. 整体架构](#5-整体架构)
  - [6.与stm32间通讯协议](#6与stm32间通讯协议)
  - [7. 未来展望](#7-未来展望)

## 1.代码主要逻辑介绍和效果展示


## 3.杂谈：
我过去从未想过，一个在设计专业混日子，且过去没有代码经历，甚至数月前只有一点python语法基础的自己竟然会接触机器视觉，甚至几乎独立编写了一个接近小项目的代码。
这次比赛虽然因为和队友们不在一个校区导致参与度不高，但是我在这次比赛真的收获了很多，很享受和队友一起努力，一起熬夜的过程，也喜欢上了机器人对抗赛。
感谢这次机甲杯校内赛，感谢我亲爱的队友们，感谢华南虎！

PS：经过综合考量，本人打算于今年从工设大二降转一级去五山的理工科专业，既是方便下个赛季加入华南虎打比赛，也是为了自己的兴趣和未来就业等。

**5月10日更新：** 转专业结果出了，降一级到物院的光电信息专业（本来想去电信或者自动化的，奈何被原专业开课卡死，且高数上分数不够，所以报了光电）。总之，大家一起加油吧！
