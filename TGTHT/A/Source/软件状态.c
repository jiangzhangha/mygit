/*

20170531


2、抽气时，贮箱压力源码为77DH，为了完成“抽气结束”，在注入参数时，需设置贮箱抽气末压值大于77DH。
另外，为了保证抽气完成，软件暂设定最大抽气时间为30分钟。
supply_mian.h的450行，修改最大抽气时间30分钟


3、补加阶段7，判断货船增压状态是否好，由于补加模型未模拟，程序设置跳过该阶段。
程序694行，2326行注释语句！！！

4、补加main程序，200行，修改eps1为0xff00


8、补加阶段9，压气机停机，转速为FFFFH，程序暂未判断。

9、补加阶段10，第333行，注释语句，跳过判断货船增压状态；

11、补加阶段9，第5547行，第8949行，注释语句，跳过通过压力判断液冷模块切换是否正常。

12、补加阶段8、补加阶段11、复压阶段，流程中p_tank_f>=p_repre_f,程序中，则为p_tank_f<=p_repre_f。？？？？？
没有520，模型未验证


14、补加阶段15，判断货船增压状态是否好，由于补加模型未模拟，程序设置跳过该阶段。
程序691行，2309行注释语句！！！


17、补加阶段18，第333行，注释语句，跳过判断货船增压状态；


19、在补加模型中，在抽气过程中，气瓶压力升高，但是贮箱气腔压力不变？？？

20、补加阶段5,27785行，27798行，判据暂定为0



*/