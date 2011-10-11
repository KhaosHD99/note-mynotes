/**
 * author: LvChengbin
 *
 * describe: to create the bubbles for wenku
 */
(function(info) {
    if(window.top != window.self) {
        return false;
    }
    /**
    * Send Log
    */
    wenku.bubble.log = {}; 
    wenku.bubble.log.imageReq = function(url){
        var n="doclog_"+(new Date()).getTime();
        var c=window[n]=new Image();//将image对象赋给全局变量，防止被当做垃圾回收，造成请求失败。
        c.onload=c.onerror=function(){
        window[n]=null; //垃圾回收
    };  
        c.src=url;
        c=null;//垃圾回收
    }

 if(typeof info == "undefined") {
     return false;
 }
 var pg = info.tpl;
     fr = pg.substring(0, pg.lastIndexOf('.')).replace("/", "_");
    
     
 if(typeof info.cookie != "undefined") {
     var mt = info.cookie[0] || 0;
     var od = info.cookie[1] || 0;
 } else {
     var mt = od = 0;
 }

 var bubble_data = {
    _switch : true,
    timestamp : Date.parse(new Date(2011, 9, 28, 20, 40, 11)),
    bubbles : [{
        bubble_name : "app_phone",
        link : "http://www.baidu.com/search/wenku/kehuduanfabu/Index.html?fr=qipao",
        show_at : [
            {page : "homenew.tpl", order : 1},
            {page : "view.tpl", order : 1},
            {page : "shop/view.tpl", order : 1},
            {page : "browse.tpl", order : 1}
        ],
        icon : "http://img.baidu.com/img/iknow/docshare/bookicon.gif",
        title : "iPhone2.0震撼升级",
        content : "文库iPhone华丽升级2.0，超逼真3D翻页，支持多格式、原文档下载，享受原汁原味的文档盛宴…",
        button : "马上体验"
    },{
        bubble_name : "kaixueji",
        link : "http://www.baidu.com/search/wenku/2011kaixue/?name=2011kaixue&fr=qipao2011kaixue",
        show_at : [
            {page : "usercenter/", order : 1},
            {page : "multiupload.tpl", order : 1}
        ],
        icon : "http://img.baidu.com/img/iknow/docshare/bookicon.gif",
        title : '轻松赢取开学超强装备',
        content : "什么？iPad、上网本、拍立得还有财富值轻松拿？！还不快去参加活动，赢取大奖！",
        button : "去拿大奖"
    },{
        bubble_name : "wedding",
        link : "http://wenku.baidu.com/topic/wedding.html?name=wedding&fr=qipaowedding",
        show_at : [
            {page : "homenew.tpl", order : 3},
            {page : "view.tpl", order : 3},
            {page : "shop/view.tpl", order : 3},
            {page : "usercenter/", order : 2},
            {page : "browse.tpl", order : 3},
            {page : "org_collect.tpl", order : 1},
            {page : "org_view.tpl", order : 1}
        ],
        icon : "http://img.baidu.com/img/iknow/docshare/bookicon.gif",
        title : "婚礼筹备实用宝典",
        content : "嘿！婚礼筹备那点事你都门儿清了吗？婚礼筹备宝典新鲜出炉，至于你信不信，反正我信了！",
        button : "获取秘籍"
    },{
        bubble_name : "guichuideng",
        link : "http://www.baidu.com/search/wenku/gcd1/index.html?fr=docbubble",
        show_at : [
            {page : "homenew.tpl", order : 2},
            {page : "browse.tpl", order : 2},
            {page : "shop/press.tpl", order : 1},
            {page : "shop/book.tpl", order : 1},
            {page : "shop/index.tpl", order : 1},
            {page : "shop/press.tpl", order : 2},
            {page : "shop/book.tpl", order : 2},
            {page : "shop/index.tpl", order : 2},
            {page : "shop/press.tpl", order : 3},
            {page : "shop/book.tpl", order : 3},
            {page : "shop/index.tpl", order : 3},
            {page : "view.tpl", order: 2},
            {page : "shop/view.tpl", order : 2}
        ],
        icon : "http://img.baidu.com/img/iknow/docshare/bookicon.gif",
        title : "鬼吹灯来了",
        content : "来文库书店看最新鬼吹灯，跟随胡八一穿越亚马逊丛林，寻踪神秘圣泉，一起来挖掘财富值宝藏！",
        button : "一起寻宝"
    }]
 };
 wenku.bubble.sendLog = function(type) {
     wenku.bubble.log.imageReq('/tongji/bubble.html?type=' + type + '&fr=' + fr + '&t=' + new Date().getTime());
 }
 var addStyle = function() {
     if(!document.getElementById('doc-Bubble-stylesheet')) {
        var bubbleStyle = document.createElement("style");
        bubbleStyle.id = "doc-Bubble-stylesheet";
        bubbleStyle.type = "text/css";
        var styleText = [
            '#docBubble{width:210px;height:121px;padding:19px 11px 0 10px;position:absolute;background:url(http://img.baidu.com/img/iknow/docshare/bubble_bg.png) no-repeat;top:30px;right:40px;text-align:left;z-index:100;}',
            '#docBubble img{display:block;border:0;}',
            '#docBubble div{height:36px;}',
            '#docBubble div span{display:block;float:right;width:11px;height:11px;background:url(http://img.baidu.com/img/iknow/docshare/bubble_bg.png) no-repeat -231px 0;cursor:pointer;margin-top:5px;font-size:0;}',
            '#docBubble div a{display:block;float:left;text-decoration:none;}',
            '#docBubble div a.bubbleTitle{margin:5px 0 0 5px;font-weight:bold;font-size:13px;}',
            '#docBubble p{padding:0 15px 0 40px;height:68px;margin-top:-8px;}',
            '#docBubble p, #docBubble p a{color:#000;font-size:12px;line-height:1.6em; _line-height:1.5em;}',
            '#docBubble p a:hover{color:#eb5200;text-decoration:none;}',
            '#docBubble div.vbtn{text-align:right;}', 
            '#docBubble div.vbtn a{float:none;text-decoration:underline;}'
        ].join('');
        try {
            bubbleStyle.appendChild(document.createTextNode(styleText));
        } catch(ex) {
            bubbleStyle.styleSheet.cssText = styleText;
        }
        document.getElementsByTagName('head')[0].appendChild(bubbleStyle);
     }
 }
 var createBubble = function(bubble, order, tpl) {
     var newBubble = document.createElement("div");
     newBubble.id = "docBubble";
     newBubble.innerHTML  =  [
         '<div>',
            '<span onmousedown="wenku.bubble.sendLog(\'bubble_shut\')" onclick="baidu.dom.g(\'docBubble\').parentNode.removeChild(baidu.dom.g(\'docBubble\'))"></span>',
            '<a onmousedown="wenku.bubble.sendLog(\'bubble_click\')" href="__LINK_ADDRESS__" target="_blank">',
                '<img src="__ICON_SRC__" />',
            '</a>',
            '<a class="bubbleTitle" onmousedown="wenku.bubble.sendLog(\'bubble_click\')" target="_blank" href="__LINK_ADDRESS__">__TITLE_TEXT__</a>',
        '</div>',
        '<p>__CONTENT_TEXT__</p>',
        '<div class="vbtn"><a onmousedown="wenku.bubble.sendLog(\'bubble_click\')" href="__LINK_ADDRESS__" target="_blank">__VIEW_BUTTON__</a></div>'
    ].join('').replace(/__LINK_ADDRESS__/g, bubble.link).replace(/__ICON_SRC__/g, bubble.icon)
              .replace(/__TITLE_TEXT__/g, bubble.title).replace(/__CONTENT_TEXT__/g, bubble.content)
              .replace(/__VIEW_BUTTON__/g, bubble.button);

     document.body.appendChild(newBubble);
     // setcookie
     tpl = tpl.split("/")[0];
     tpl = tpl.replace(".", "-");
     baidu.cookie.set(tpl + "_docBubble", bubble_data.timestamp + "_" + order, {"path" : "/", "expires" : 64800000});
 }


 if(bubble_data._switch == false) {
     return false;
 }

 for(var i = 0, len = bubble_data.bubbles.length; i < len; i++) {

     for(var j = 0, sLen = bubble_data.bubbles[i].show_at.length; j < sLen; j++) {

         var thisBubble = bubble_data.bubbles[i], thisPage = thisBubble.show_at[j].page;

         if(thisPage == pg || (thisPage.lastIndexOf("/") == (thisPage.length-1) && (pg.split("/")[0] + "/") == thisPage)) {
             if(mt == bubble_data.timestamp) {
                 if(thisBubble.show_at[j].order == (parseInt(od)+1)) {
                     wenku.bubble.sendLog('bubble');
                     addStyle();
                     return createBubble(thisBubble, (parseInt(od)+1), pg);
                 }
             } else if(thisBubble.show_at[j].order == 1){
                 wenku.bubble.sendLog('bubble');
                 addStyle();   
                 return createBubble(thisBubble, 1, pg);
             }
         }
     }
 }
})(wenku.bubble.info);
/**
 * ICONS :
 * http://img.baidu.com/img/iknow/docshare/bookicon.gif // Book
 * http://hiphotos.baidu.com/baidu/pic/item/76094b36ce1430b5a2cc2b47.gif // paper plane
 */
