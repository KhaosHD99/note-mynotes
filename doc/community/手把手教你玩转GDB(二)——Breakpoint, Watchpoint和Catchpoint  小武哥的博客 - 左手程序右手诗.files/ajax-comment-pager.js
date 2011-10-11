(function() {

var xmlHttp;
var anchor;

function getXmlHttpObject() {
	var xmlHttp = null;
	try {
		xmlHttp = new XMLHttpRequest();
	} catch(e) {
		try {
			xmlHttp = new ActiveXObject("Msxml2.XMLHTTP");
		} catch(e) {
			xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
		}
	}
	return xmlHttp;
}

function change(wpurl, navigation) {
	xmlHttp = getXmlHttpObject();
	if (xmlHttp == null) {
		alert ("Oop! Browser does not support HTTP Request.");
		return;
	}

	if (!$('cp_post_id')) {
		window.location = wpurl;
		return;
	}
	var postId = $('cp_post_id').innerHTML

	var commentPage = 1;
	if (/comment-page-/i.test(wpurl)) {
		commentPage = wpurl.split(/^.*comment-page-/)[1].split(/(\/|#|&).*$/)[0];
	} else if (/cpage=/i.test(wpurl)) {
		commentPage = wpurl.split(/^.*cpage=/)[1].split(/(\/|#|&).*$/)[0];
	}

	var url = wpurl.split(/#.*$/)[0];
	url += /\?/i.test(wpurl) ? '&' : '?';
	url += 'action=cpage_ajax&post=' + postId + '&page=' + commentPage;

	if (!anchor) {
		anchor = wpurl.split(/^.*#/)[1];
	}

	xmlHttp.onreadystatechange = function(){runChange(anchor, navigation)};
	xmlHttp.open("GET", url, true);
	xmlHttp.send(null);
}

function runChange(anchor, navigation) {
	var comments = $(ajaxCommnetsPagerCommentsId);

	if (xmlHttp.readyState < 4 && !$('ajax-comment-loader')) {
		document.body.style.cursor = 'wait';
		navigation.innerHTML = '<span id="ajax-comment-loader">' + ajaxCommnetsPagerAjaxLoader + '</span>';

		var opacity = 0.5;
		setStyle(comments, 'opacity', opacity);
		setStyle(comments, 'MozOpacity', opacity);
		setStyle(comments, 'KhtmlOpacity', opacity);
		setStyle(comments, 'filter', 'alpha(opacity=' + opacity * 100 + ')');

	} else if (xmlHttp.readyState == 4 || xmlHttp.readyState=="complete") {
		responses = xmlHttp.responseText.split('<!-- AJAX_COMMENT_PAGER_SEPARATOR_BY_MG12 -->');

		comments.innerHTML = responses[0];
		var opacity = 1;
		setStyle(comments, 'opacity', opacity);
		setStyle(comments, 'MozOpacity', opacity);
		setStyle(comments, 'KhtmlOpacity', opacity);
		setStyle(comments, 'filter', 'alpha(opacity=' + opacity * 100 + ')');

		gotoAnchor(anchor);

		navigation.innerHTML = responses[1];
		init();
		document.body.style.cursor = 'auto';
	}
}

function init() {
	var pagerList = getElementsByClassName('page-numbers', 'a', document);
	if (pagerList.length <= 0) {
		return;
	}
	var navigation = pagerList[0].parentNode;
	if (navigation) {
		for (var i = 0; i < pagerList.length; i++) {
			addEvent(pagerList[i], 'click', function(W3CEvent) {
				change(this.href.split(/(\?|&)action=cpage_ajax.*$/)[0], navigation);
				preventDefault(W3CEvent);
			});
		}
	}
}

function $(id) {
	return document.getElementById(id);
}

function setStyle(element, key, value) {
	element.style[key] = value;
}

function cumulativeOffset(element) {
	var valueT = 0, valueL = 0;
	do {
		valueT += element.offsetTop  || 0;
		valueL += element.offsetLeft || 0;
		element = element.offsetParent;
	} while (element);
	return [valueL, valueT];
}

function gotoAnchor(id) {
	var pos = cumulativeOffset($(id));
	var left = pos[0];
	var top = pos[1];
	window.scrollTo(left, top);
}

function isCompatible(other) {
	if( other===false 
		|| !Array.prototype.push
		|| !Object.hasOwnProperty
		|| !document.createElement
		|| !document.getElementsByTagName
		) {
		alert('TR- if you see this message isCompatible is failing incorrectly.');
		return false;
	}
	return true;
}

function getElementsByClassName(className, tag, parent){
	parent = parent || document;

	var allTags = (tag == "*" && parent.all) ? parent.all : parent.getElementsByTagName(tag);
	var matchingElements = new Array();

	className = className.replace(/\-/g, "\\-");
	var regex = new RegExp("(^|\\s)" + className + "(\\s|$)");
	
	var element;
	for(var i=0; i<allTags.length; i++){
		element = allTags[i];
		if(regex.test(element.className)){
			matchingElements.push(element);
		}
	}

	return matchingElements;
};

function addEvent( node, type, listener ) {
	if(!isCompatible()) { return false }

	if (node.addEventListener) {
		node.addEventListener( type, listener, false );
		return true;
	} else if(node.attachEvent) {
		node['e'+type+listener] = listener;
		node[type+listener] = function(){node['e'+type+listener]( window.event );}
		node.attachEvent( 'on'+type, node[type+listener] );
		return true;
	}

	return false;
};

function preventDefault(eventObject) {
	eventObject = eventObject || getEventObject(eventObject);
	if(eventObject.preventDefault) {
		eventObject.preventDefault();
	} else {
		eventObject.returnValue = false;
	}
}

String.prototype._$$split = String.prototype._$$split || String.prototype.split;
String.prototype.split = function (s, limit) {
	if (!(s instanceof RegExp))
		return String.prototype._$$split.apply(this, arguments);

	var	flags = (s.global ? "g" : "") + (s.ignoreCase ? "i" : "") + (s.multiline ? "m" : ""),
		s2 = new RegExp("^" + s.source + "$", flags),
		output = [],
		origLastIndex = s.lastIndex,
		lastLastIndex = 0,
		i = 0, match, lastLength;

	if (limit === undefined || +limit < 0) {
		limit = false;
	} else {
		limit = Math.floor(+limit);
		if (!limit)
			return [];
	}

	if (s.global)
		s.lastIndex = 0;
	else
		s = new RegExp(s.source, "g" + flags);

	while ((!limit || i++ <= limit) && (match = s.exec(this))) {
		var emptyMatch = !match[0].length;

		if (emptyMatch && s.lastIndex > match.index)
			s.lastIndex--;

		if (s.lastIndex > lastLastIndex) {
			if (match.length > 1) {
				match[0].replace(s2, function () {
					for (var j = 1; j < arguments.length - 2; j++) {
						if (arguments[j] === undefined)
							match[j] = undefined;
					}
				});
			}

			output = output.concat(this.slice(lastLastIndex, match.index));
			if (1 < match.length && match.index < this.length)
				output = output.concat(match.slice(1));
			lastLength = match[0].length;
			lastLastIndex = s.lastIndex;
		}

		if (emptyMatch)
			s.lastIndex++;
	}

	output = lastLastIndex === this.length ?
		(s.test("") && !lastLength ? output : output.concat("")) :
		(limit ? output : output.concat(this.slice(lastLastIndex)));
	s.lastIndex = origLastIndex;
	return output;
};

if (document.addEventListener) {
	document.addEventListener("DOMContentLoaded", init, false);

} else if (/MSIE/i.test(navigator.userAgent)) {
	document.write('<script id="__ie_onload_for_ajax_comment_pager" defer src="javascript:void(0)"></script>');
	var script = $('__ie_onload_for_ajax_comment_pager');
	script.onreadystatechange = function() {
		if (this.readyState == 'complete') {
			init();
		}
	}

} else if (/WebKit/i.test(navigator.userAgent)) {
	var _timer = setInterval( function() {
		if (/loaded|complete/.test(document.readyState)) {
			clearInterval(_timer);
			init();
		}
	}, 10);

} else {
	window.onload = function(e) {
		init();
	}
}

})();
