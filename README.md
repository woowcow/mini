https://www.woowcow.com/

mini → 簡易版
mini with watchdog → 包含watchdog版

關於牛圈
在1976年唐山地震，1995年阪神大地震1999年台灣集集大地震(921)發生前不少人家中日光燈在關閉狀況下仍然持續發亮。 地震前空氣中會出現大量電磁異常，會使空氣中電子互相撞擊，互相撞擊時會使日光燈內水銀蒸汽放出紫外線使管內螢光漆發光，產生可見光。此現象發生在震度較大時（約震央規模6.0以上），過小或過遠則無發光反應。
牛圈利用此發光現象應用Arduino nano加上光照感測器（GY-30-HB1750I）簡易電子零件來偵測日光燈管是否有發光反應，如果偵測到發光反應，將使用鳴笛器發出聲音通知。 目前提供低成本可偵測方法，在我們測試期間，只發生過一次芮氏規模 6.0以上地震，待全球更多地方使用後，確認此實驗方法可行性。目前預計於台灣、日本、中國及美國等地佈點收集數據。我們提供線路圖及相關程式，也歡迎所有有興趣的使用者一起加入我們的實驗。 

預計更新事項：
1)建置人工回報系統，蒐集亮度資料建立亮度跟地震發生相關數值，用來預報可能發生地震規模大小之使用。
2)連接網路自動回報相關數據。
3)建立全球化發生區域預警通知系統。

*目前計畫採用開放原始碼贊助方式，待時間驗證及足夠的贊助經費逐步完成計畫

# (GitHub-Flavored) Markdown Editor

Basic useful feature list:

 * Ctrl+S / Cmd+S to save the file
 * Ctrl+Shift+S / Cmd+Shift+S to choose to save as Markdown or HTML
 * Drag and drop a file into here to load it
 * File contents are saved in the URL so you can share files


I'm no good at writing sample / filler text, so go write something yourself.

Look, a list!

 * foo
 * bar
 * baz

And here's some code! :+1:

```javascript
$(function(){
  $('div').html('I am a div.');
});
```

This is [on GitHub](https://github.com/jbt/markdown-editor) so let me know if I've b0rked it somewhere.


Props to Mr. Doob and his [code editor](http://mrdoob.com/projects/code-editor/), from which
the inspiration to this, and some handy implementation hints, came.

### Stuff used to make this:

 * [markdown-it](https://github.com/markdown-it/markdown-it) for Markdown parsing
 * [CodeMirror](http://codemirror.net/) for the awesome syntax-highlighted editor
 * [highlight.js](http://softwaremaniacs.org/soft/highlight/en/) for syntax highlighting in output code blocks
 * [js-deflate](https://github.com/dankogai/js-deflate) for gzipping of data to make it fit in URLs
