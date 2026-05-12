(function () {
  var upstreamOrigin = "https://oi-wiki.org";

  function currentUpstreamUrl() {
    var path = window.location.pathname || "/";
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
