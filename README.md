[https://www.woowcow.com/](https://www.woowcow.com/)

# 牛圈

目錄原始碼:
 * [mini → 簡易版 (HB1750I)](https://github.com/woowcow/mini/tree/master/mini)
 * [mini with watchdog → 包含watchdog版 (HB1750I)](https://github.com/woowcow/mini/tree/master/mini%20with%20watchdog)
 * [OPT3001 mini → 簡易版 (OPT3001)](https://github.com/woowcow/mini/tree/master/OPT3001%20mini)
 * [OPT3001 mini with watchdog → 包含watchdog版 (OPT3001)](https://github.com/woowcow/mini/tree/master/OPT3001%20mini%20with%20watchdog)
 * [Voltage-5V with watchdog → 電壓5v版包含watchdog版](https://github.com/woowcow/mini/tree/master/Voltage-5V%20with%20watchdog)

關於牛圈
在1976年唐山地震，1995年阪神大地震1999年台灣集集大地震(921)發生前不少人家中日光燈在關閉狀況下仍然持續發亮。 地震前空氣中會出現大量電磁異常，會使空氣中電子互相撞擊，互相撞擊時會使日光燈內水銀蒸汽放出紫外線使管內螢光漆發光，產生可見光。此現象發生在震度較大時（約震央規模6.0以上），過小或過遠則無發光反應。
牛圈利用此發光現象應用Arduino nano加上光照感測器（GY-30-HB1750I）簡易電子零件來偵測日光燈管是否有發光反應，如果偵測到發光反應，將使用鳴笛器發出聲音通知。 目前提供低成本可偵測方法，在我們測試期間，只發生過一次芮氏規模 6.0以上地震，待全球更多地方使用後，確認此實驗方法可行性。目前預計於台灣、日本、中國及美國等地佈點收集數據。我們提供線路圖及相關程式，也歡迎所有有興趣的使用者一起加入我們的實驗。 

# 關於聲音警報
 * 亮度播報方式為:音階後面接上播報數字
 * [1 ~ 9:一聲響~九聲響] [0:十聲響]

例: 
 * 偵測到亮度為5: [音階][五聲響] 
 * 偵測到亮度為10: [音階][一聲響][間斷][十聲響]
 * 可到Youtube開啟字幕會有備註說明
[https://www.youtube.com/watch?v=3yWv7hhuF1Y](https://www.youtube.com/watch?v=3yWv7hhuF1Y)


# 預計更新事項

 * 建置人工回報系統，蒐集亮度資料建立亮度跟地震發生相關數值，用來預報可能發生地震規模大小之使用。
 * 連接網路自動回報相關數據。
 * 建立全球化發生區域預警通知系統。

*目前計畫採用開放原始碼贊助方式，待時間驗證及足夠的贊助經費逐步完成計畫

# 更新記錄
 * 2017-09-05 發現有發光反應時會產生微量電壓，新增電壓版本可偵測 5v 內電壓
 * 2017-07-20 新增感測 IC OPT3001 (CJMCU-3001)最低偵測亮度 0.01lux
 * 2017-06-24 取消最低偵測亮度 1lux 直接輸出BH1750數值
