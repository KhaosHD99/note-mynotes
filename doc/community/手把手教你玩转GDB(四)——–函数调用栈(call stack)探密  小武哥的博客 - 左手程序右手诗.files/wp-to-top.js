var toTop = {
	init: function(){
		toTop.animScroll = new YAHOO.util.Anim(null);
	},
	
	scroll: function(){
		if(toTop.getScrolledAmountY() > 0){
			YAHOO.util.Dom.setStyle('takeMeUpContainer', 'display', 'block');
			toTop.animFade = new YAHOO.util.Anim('takeMeUpContainer');
			toTop.animFade.attributes.opacity = {from: 0, to: 1};
			toTop.animFade.animate();
		}
		else if(toTop.getScrolledAmountY() == 0){
			toTop.animFade = new YAHOO.util.Anim('takeMeUpContainer');
			toTop.animFade.attributes.opacity = {from: YAHOO.util.Dom.getStyle('takeMeUpContainer', 'opacity'), to: 0};
			toTop.animFade.animate();
			toTop.animFade.onComplete.subscribe(function() {
				YAHOO.util.Dom.setStyle('takeMeUpContainer', 'display', 'none');
			});
		}
	},
	
	getScrolledAmount: function(){
		var x,y;
		if (typeof(self.pageYOffset) != 'undefined' ){ // all but
			x = self.pageXOffset;
			y = self.pageYOffset;
		}else if (document.documentElement && typeof(document.documentElement.scrollTop)!='undefined'){
			// IE Standards mode
			x = document.documentElement.scrollLeft;
			y = document.documentElement.scrollTop;
		}else if(document.body){ // IE Quirks mode
			x = document.body.scrollLeft;
			y = document.body.scrollTop;
		}

		var values = new Array();
		values.x = x;
		values.y = y;
		return values;
	},

	getScrolledAmountY: function(){
		var y;
		if (typeof(self.pageYOffset) != 'undefined' ){ // all but
		y = self.pageYOffset;
		}else if (document.documentElement && typeof(document.documentElement.scrollTop)!='undefined'){
			// IE Standards mode
			y = document.documentElement.scrollTop;
		}else if(document.body){ // IE Quirks mode
			y = document.body.scrollTop;
		}

		return y;
	},

	setAttr: function(a, v, u) {
		window.scroll(0, v);
	},
	
	scrollToTop: function(e){
		var scrolledAmountY = toTop.getScrolledAmountY();
		toTop.animScroll.attributes.scroll = {from: scrolledAmountY, to : 0};
		toTop.animScroll.duration = 0.5;
		toTop.animScroll.setAttribute = toTop.setAttr;
		toTop.animScroll.animate();
	}
};
toTop.init();
YAHOO.util.Event.on(window, 'scroll', toTop.scroll);
YAHOO.util.Event.on('takeMeUp', 'click', toTop.scrollToTop);