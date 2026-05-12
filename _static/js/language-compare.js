(function () {
  var upstreamOrigin = "https://oi-wiki.org";
  var scriptPath = document.currentScript && document.currentScript.src
    ? new URL(document.currentScript.src).pathname
    : "/_static/js/language-compare.js";
  var siteBasePath = scriptPath.replace(/_static\/js\/language-compare\.js(?:\?.*)?$/, "");

  function currentUpstreamUrl() {
    var path = window.location.pathname || "/";
    if (siteBasePath !== "/" && path.indexOf(siteBasePath) === 0) {
      path = path.slice(siteBasePath.length - 1);
    }
    return upstreamOrigin + path + window.location.hash;
  }

  function addCompareButton() {
    var existing = document.querySelector(".oiwiki-language-compare");
    if (existing) {
      existing.href = currentUpstreamUrl();
      return;
    }

    var link = document.createElement("a");
    link.className = "oiwiki-language-compare";
    link.href = currentUpstreamUrl();
    link.target = "_blank";
    link.rel = "noopener noreferrer";
    link.textContent = "Chinese original";
    link.title = "Open the matching upstream Chinese page";

    document.body.appendChild(link);
  }

  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", addCompareButton);
  } else {
    addCompareButton();
  }

  if (window.document$ && typeof window.document$.subscribe === "function") {
    window.document$.subscribe(addCompareButton);
  }

  window.addEventListener("popstate", addCompareButton);
})();
