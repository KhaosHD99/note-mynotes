var isCompatible=function(){if(navigator.appVersion.indexOf('MSIE')!==-1&&parseFloat(navigator.appVersion.split('MSIE')[1])<6){return false;}return true;};var startUp=function(){mediaWiki.loader.register([["site","1317159817",[],"site"],["startup",1317237768,[],"startup"],["user","1311020640",[],"user"],["user.options","1311020640",[],"private"],["filepage","1311020640",[]],["skins.vector","1311020640",[]],["skins.simple","1311020640",[]],["jquery",1317057911,[]],["jquery.async","1311020640",[]],["jquery.appear","1311020640",[]],["jquery.autoEllipsis","1311020640",["jquery.highlightText"]],["jquery.checkboxShiftClick","1311020640",[]],["jquery.client","1311020640",[]],["jquery.collapsibleTabs","1311020640",[]],["jquery.color","1311020640",[]],["jquery.cookie","1311020640",[]],["jquery.delayedBind","1311020640",[]],["jquery.expandableField","1311020640",[]],["jquery.highlightText",1315567972,[]],["jquery.placeholder","1311020640",[]],["jquery.json","1311020640",[]],["jquery.localize",
1311631364,[]],["jquery.suggestions","1311020640",["jquery.autoEllipsis"]],["jquery.tabIndex","1311020640",[]],["jquery.textSelection",1316507813,[]],["jquery.tipsy","1311020640",[]],["jquery.ui.core","1311020640",["jquery"]],["jquery.ui.widget","1311020640",[]],["jquery.ui.mouse","1311020640",["jquery.ui.widget"]],["jquery.ui.position","1311020640",[]],["jquery.ui.draggable","1311020640",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget"]],["jquery.ui.droppable","1311020640",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget","jquery.ui.draggable"]],["jquery.ui.resizable","1311020640",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"]],["jquery.ui.selectable","1311020640",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"]],["jquery.ui.sortable","1311020640",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"]],["jquery.ui.accordion","1311020640",["jquery.ui.core","jquery.ui.widget"]],["jquery.ui.autocomplete","1311020640",["jquery.ui.core","jquery.ui.widget",
"jquery.ui.position"]],["jquery.ui.button","1311020640",["jquery.ui.core","jquery.ui.widget"]],["jquery.ui.datepicker","1311020640",["jquery.ui.core"]],["jquery.ui.dialog","1311020640",["jquery.ui.core","jquery.ui.widget","jquery.ui.button","jquery.ui.draggable","jquery.ui.mouse","jquery.ui.position","jquery.ui.resizable"]],["jquery.ui.progressbar","1311020640",["jquery.ui.core","jquery.ui.widget"]],["jquery.ui.slider","1311020640",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"]],["jquery.ui.tabs","1311020640",["jquery.ui.core","jquery.ui.widget"]],["jquery.effects.core","1311020640",["jquery"]],["jquery.effects.blind","1311020640",["jquery.effects.core"]],["jquery.effects.bounce","1311020640",["jquery.effects.core"]],["jquery.effects.clip","1311020640",["jquery.effects.core"]],["jquery.effects.drop","1311020640",["jquery.effects.core"]],["jquery.effects.explode","1311020640",["jquery.effects.core"]],["jquery.effects.fold","1311020640",["jquery.effects.core"]],[
"jquery.effects.highlight","1311020640",["jquery.effects.core"]],["jquery.effects.pulsate","1311020640",["jquery.effects.core"]],["jquery.effects.scale","1311020640",["jquery.effects.core"]],["jquery.effects.shake","1311020640",["jquery.effects.core"]],["jquery.effects.slide","1311020640",["jquery.effects.core"]],["jquery.effects.transfer","1311020640",["jquery.effects.core"]],["mediawiki",1315848487,[]],["mediawiki.util",1315424519,["jquery.checkboxShiftClick","jquery.client","jquery.placeholder"]],["mediawiki.Uri",1314636075,[]],["mediawiki.action.history","1311020640",["mediawiki.legacy.history"],"mediawiki.action.history"],["mediawiki.action.edit","1311020640",[]],["mediawiki.action.view.rightClickEdit","1311020640",[]],["mediawiki.page.startup",1317056302,["jquery.client"]],["mediawiki.special.preferences","1317090696",[]],["mediawiki.special.search","1311020640",[]],["mediawiki.language","1311020640",[]],["mediawiki.legacy.ajax","1317090508",["mediawiki.legacy.wikibits"]],[
"mediawiki.legacy.ajaxwatch","1311020640",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.block","1311020640",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.commonPrint","1311020640",[]],["mediawiki.legacy.config","1311020640",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.diff","1311020640",["mediawiki.legacy.wikibits"],"mediawiki.action.history"],["mediawiki.legacy.edit","1311020640",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.enhancedchanges","1311020640",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.history","1311020640",["mediawiki.legacy.wikibits"],"mediawiki.action.history"],["mediawiki.legacy.htmlform","1311020640",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.IEFixes","1311020640",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.metadata","1317090521",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.mwsuggest","1317090508",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.prefs","1311020640",["mediawiki.legacy.wikibits","mediawiki.legacy.htmlform"]],[
"mediawiki.legacy.preview","1311020640",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.protect","1311020640",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.search","1311020640",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.shared",1315837643,[]],["mediawiki.legacy.oldshared","1311020640",[]],["mediawiki.legacy.upload","1311020640",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.wikibits","1317090508",["mediawiki.language"]],["mediawiki.legacy.wikiprintable","1311020640",[]],["ext.gadget.Navigation_popups","1311020640",[]],["ext.gadget.Twinkle","1317143470",["mediawiki.util","jquery.ui.dialog","jquery.tipsy"]],["ext.gadget.HotCat","1311020640",[]],["ext.gadget.textareasansserif","1311020640",[]],["ext.gadget.purgetab","1311020640",["mediawiki.util"]],["ext.gadget.UTCLiveClock","1311020640",[]],["ext.gadget.dropdown-menus","1311020640",[]],["ext.gadget.NoSmallFonts","1311020640",[]],["ext.gadget.MenuToTabs","1311020640",[]],["ext.gadget.MenuTabsToggle","1316883004",[]],[
"ext.gadget.Blackskin","1311020640",[]],["ext.gadget.widensearch","1311020640",[]],["ext.gadget.DejaVu_Sans","1311020640",[]],["ext.articleFeedback.startup","1311020640",["mediawiki.util"]],["ext.articleFeedback","1317090508",["jquery.ui.dialog","jquery.ui.button","jquery.articleFeedback","jquery.cookie","jquery.clickTracking"]],["ext.articleFeedback.dashboard","1311020640",[]],["jquery.articleFeedback","1317090508",["jquery.appear","jquery.tipsy","jquery.json","jquery.localize","jquery.ui.dialog","jquery.ui.button","jquery.cookie","jquery.clickTracking"]],["ext.wikihiero",1315426567,[]],["ext.checkUser","1311020640",["mediawiki.legacy.block"]],["ext.collection.jquery.json","1311020640",[]],["ext.collection.jquery.jstorage","1311020640",["ext.collection.jquery.json"]],["ext.collection.suggest","1311020640",["ext.collection.bookcreator"]],["ext.collection","1311020640",["ext.collection.bookcreator","jquery.ui.sortable"]],["ext.collection.bookcreator","1311020640",[
"ext.collection.jquery.jstorage"]],["ext.collection.checkLoadFromLocalStorage","1311020640",["ext.collection.jquery.jstorage"]],["ext.vector.collapsibleNav","1317090508",["jquery.client","jquery.cookie","jquery.tabIndex"],"ext.vector"],["ext.vector.collapsibleTabs","1311020640",["jquery.collapsibleTabs","jquery.delayedBind"],"ext.vector"],["ext.vector.editWarning","1317090508",[],"ext.vector"],["ext.vector.expandableSearch","1311020640",["jquery.client","jquery.expandableField","jquery.delayedBind"],"ext.vector"],["ext.vector.footerCleanup","1311020640",[],"ext.vector"],["ext.vector.sectionEditLinks","1311020640",["jquery.cookie","jquery.clickTracking"],"ext.vector"],["ext.vector.simpleSearch","1317090508",["jquery.client","jquery.suggestions","jquery.autoEllipsis","jquery.placeholder"],"ext.vector"],["contentCollector","1311020640",[],"ext.wikiEditor"],["jquery.wikiEditor","1317090522",["jquery.client","jquery.textSelection","jquery.delayedBind"],"ext.wikiEditor"],[
"jquery.wikiEditor.iframe","1311020640",["jquery.wikiEditor","contentCollector"],"ext.wikiEditor"],["jquery.wikiEditor.dialogs","1311020640",["jquery.wikiEditor","jquery.wikiEditor.toolbar","jquery.ui.dialog","jquery.ui.button","jquery.ui.draggable","jquery.ui.resizable","jquery.tabIndex"],"ext.wikiEditor"],["jquery.wikiEditor.highlight","1311020640",["jquery.wikiEditor","jquery.wikiEditor.iframe"],"ext.wikiEditor"],["jquery.wikiEditor.preview","1311020640",["jquery.wikiEditor"],"ext.wikiEditor"],["jquery.wikiEditor.previewDialog","1311020640",["jquery.wikiEditor","jquery.wikiEditor.dialogs"],"ext.wikiEditor"],["jquery.wikiEditor.publish","1311020640",["jquery.wikiEditor","jquery.wikiEditor.dialogs"],"ext.wikiEditor"],["jquery.wikiEditor.templateEditor","1311020640",["jquery.wikiEditor","jquery.wikiEditor.iframe","jquery.wikiEditor.dialogs"],"ext.wikiEditor"],["jquery.wikiEditor.templates","1311020640",["jquery.wikiEditor","jquery.wikiEditor.iframe"],"ext.wikiEditor"],[
"jquery.wikiEditor.toc","1311020640",["jquery.wikiEditor","jquery.wikiEditor.iframe","jquery.ui.draggable","jquery.ui.resizable","jquery.autoEllipsis","jquery.color"],"ext.wikiEditor"],["jquery.wikiEditor.toolbar","1311020640",["jquery.wikiEditor"],"ext.wikiEditor"],["ext.wikiEditor","1311020640",["jquery.wikiEditor"],"ext.wikiEditor"],["ext.wikiEditor.dialogs","1311020640",["ext.wikiEditor","ext.wikiEditor.toolbar","jquery.wikiEditor.dialogs","jquery.suggestions"],"ext.wikiEditor"],["ext.wikiEditor.highlight","1311020640",["ext.wikiEditor","jquery.wikiEditor.highlight"],"ext.wikiEditor"],["ext.wikiEditor.preview","1311020640",["ext.wikiEditor","jquery.wikiEditor.preview"],"ext.wikiEditor"],["ext.wikiEditor.previewDialog","1317177662",["ext.wikiEditor","jquery.wikiEditor.previewDialog"],"ext.wikiEditor"],["ext.wikiEditor.publish","1311020640",["ext.wikiEditor","jquery.wikiEditor.publish"],"ext.wikiEditor"],["ext.wikiEditor.templateEditor","1311020640",["ext.wikiEditor",
"ext.wikiEditor.highlight","jquery.wikiEditor.templateEditor"],"ext.wikiEditor"],["ext.wikiEditor.templates","1311020640",["ext.wikiEditor","ext.wikiEditor.highlight","jquery.wikiEditor.templates"],"ext.wikiEditor"],["ext.wikiEditor.toc","1311020640",["ext.wikiEditor","ext.wikiEditor.highlight","jquery.wikiEditor.toc"],"ext.wikiEditor"],["ext.wikiEditor.tests.toolbar","1311020640",["ext.wikiEditor.toolbar"],"ext.wikiEditor"],["ext.wikiEditor.toolbar",1315424476,["ext.wikiEditor","ext.wikiEditor.toolbar.i18n","jquery.wikiEditor.toolbar","jquery.cookie","jquery.async"],"ext.wikiEditor"],["ext.wikiEditor.toolbar.i18n","1311020640",[],"ext.wikiEditor"],["ext.prefSwitch","1311020640",["jquery.client"]],["jquery.clickTracking","1311020640",["jquery.cookie"]],["ext.clickTracking","1311020640",["jquery.clickTracking"]],["ext.clickTracking.special","1311020640",["jquery.ui.datepicker","jquery.ui.dialog"]],["ext.UserBuckets","1311020640",["jquery.clickTracking","jquery.cookie",
"ext.UserBuckets.AccountCreationUserBucket"]],["ext.UserBuckets.AccountCreationUserBucket","1311020640",["jquery.clickTracking"]],["ext.wikiLove.icon",1313704446,[]],["ext.wikiLove.defaultOptions","1317090519",[]],["ext.wikiLove.startup",1317237768,["ext.wikiLove.defaultOptions","jquery.ui.dialog","jquery.ui.button","jquery.localize","jquery.elastic"]],["ext.wikiLove.local","1312944211",[]],["ext.wikiLove.init","1311020640",["ext.wikiLove.startup"]],["jquery.elastic",1313704427,[]],["ext.moodBar.init","1317090933",["jquery.cookie","jquery.client"]],["ext.moodBar.core","1317090547",["mediawiki.util","ext.moodBar.init","jquery.localize","jquery.moodBar"]],["jquery.moodBar",1311631334,["mediawiki.util"]],["ext.babel",1316607002,[]]]);mediaWiki.config.set({"wgLoadScript":"//bits.wikimedia.org/en.wikipedia.org/load.php","debug":false,"skin":"vector","stylepath":"//bits.wikimedia.org/skins-1.17","wgUrlProtocols":
"http\\:\\/\\/|https\\:\\/\\/|ftp\\:\\/\\/|irc\\:\\/\\/|gopher\\:\\/\\/|telnet\\:\\/\\/|nntp\\:\\/\\/|worldwind\\:\\/\\/|mailto\\:|news\\:|svn\\:\\/\\/|git\\:\\/\\/|mms\\:\\/\\/|\\/\\/","wgArticlePath":"/wiki/$1","wgScriptPath":"/w","wgScriptExtension":".php","wgScript":"/w/index.php","wgVariantArticlePath":false,"wgActionPaths":[],"wgServer":"//en.wikipedia.org","wgUserLanguage":"en","wgContentLanguage":"en","wgVersion":"1.17wmf1","wgEnableAPI":true,"wgEnableWriteAPI":true,"wgSeparatorTransformTable":["",""],"wgDigitTransformTable":["",""],"wgMainPageTitle":"Main Page","wgFormattedNamespaces":{"-2":"Media","-1":"Special","0":"","1":"Talk","2":"User","3":"User talk","4":"Wikipedia","5":"Wikipedia talk","6":"File","7":"File talk","8":"MediaWiki","9":"MediaWiki talk","10":"Template","11":"Template talk","12":"Help","13":"Help talk","14":"Category","15":"Category talk","100":"Portal","101":"Portal talk","108":"Book","109":"Book talk"},"wgNamespaceIds":{"media":-2,"special":-1,"":0,"talk":
1,"user":2,"user_talk":3,"wikipedia":4,"wikipedia_talk":5,"file":6,"file_talk":7,"mediawiki":8,"mediawiki_talk":9,"template":10,"template_talk":11,"help":12,"help_talk":13,"category":14,"category_talk":15,"portal":100,"portal_talk":101,"book":108,"book_talk":109,"wp":4,"wt":5,"image":6,"image_talk":7},"wgSiteName":"Wikipedia","wgFileExtensions":["png","gif","jpg","jpeg","xcf","pdf","mid","ogg","ogv","svg","djvu","tiff","tif","oga"],"wgDBname":"enwiki","wgExtensionAssetsPath":"//bits.wikimedia.org/w/extensions-1.17","wgMWSuggestTemplate":"//en.wikipedia.org/w/api.php?action=opensearch\x26search={searchTerms}\x26namespace={namespaces}\x26suggest","wgCollectionVersion":"1.4","wgCollapsibleNavBucketTest":false,"wgCollapsibleNavForceNewVersion":false,"wgArticleFeedbackSMaxage":2592000,"wgArticleFeedbackCategories":["Article Feedback Pilot","Article Feedback","Article Feedback Additional Articles"],"wgArticleFeedbackBlacklistCategories":["Article Feedback Blacklist"],
"wgArticleFeedbackLotteryOdds":100,"wgArticleFeedbackTracking":{"buckets":{"track":"0.27","ignore":"99.73"},"version":8,"expires":30,"tracked":false},"wgArticleFeedbackOptions":{"buckets":{"show":100,"hide":0},"version":8,"expires":30,"tracked":false},"wgArticleFeedbackNamespaces":[0],"wgArticleFeedbackWhatsThisPage":"Wikipedia:Article Feedback Tool","mbConfig":{"validTypes":["happy","sad","confused"],"userBuckets":[],"bucketConfig":{"buckets":{"feedback":80,"share":10,"editing":10},"version":3,"expires":30},"infoUrl":"http://www.mediawiki.org/wiki/MoodBar","privacyUrl":"//wikimediafoundation.org/wiki/Feedback_policy","disableExpiration":365}});};if(isCompatible()){document.write("\x3cscript src=\"//bits.wikimedia.org/en.wikipedia.org/load.php?debug=false\x26amp;lang=en\x26amp;modules=jquery%7Cmediawiki\x26amp;only=scripts\x26amp;skin=vector\x26amp;version=20110926T172500Z\" type=\"text/javascript\"\x3e\x3c/script\x3e");}delete isCompatible;;

/* cache key: enwiki:resourceloader:filter:minify-js:5:2e4d421d76e67f08b914ead14463f244 */