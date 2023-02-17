console.log('begin');
feather.replace();

const colorsLight = {
  mainBg: '#f1faee',
  mainShadow: '#f1faee',
  mainText: '#1d3557',
  mainLogo: '#1d3557',
  mainLink: '#457b9d',
  mainRed: '#e63946',
  mainLight: '#a8dadc',
  newShadow: '#e5e5e5',
  newBlue: '#219ebc',
  htmlBg: 'white'
};

const colorsDark = {
  mainBg: '#1d3557',
  mainShadow: '#1d3557',
  mainText: '#f1faee',
  mainLogo: '#8ecae6',
  mainLink: '#e63946',
  mainRed: '#ffb703',
  mainLight: '#ffb703',
  newShadow: '#14213d',
  newBlue: '#fb8500',
  htmlBg: '#023047'
};

let jsonObject = {};
let nightMode = (() => {
  const thisURL = new URL(window.location.toLocaleString());
  if (thisURL.searchParams.has('darkmode')) {
    return !!JSON.parse(thisURL.searchParams.get('darkmode'));
  } else {
    return false;
  }
})();

setInterval(() => {
  getAll();
  updateData(jsonObject);
}, 2000);

const getAll = () => {
  axios.get('/data')
    .then(function (response) {
      jsonObject = response.data;
    });
}

const updateData = (data) => {
  if (Object.keys(data).length) {
    document.getElementById("uptime").innerHTML = data.uptime;
    document.getElementById("ip").innerHTML = data.ipaddr;
    document.getElementById("heap").innerHTML = data.free_heap;
    document.getElementById("cpu").innerHTML = data.cpu;
    document.getElementById("flash").innerHTML = data.flash;
    document.getElementById("version").innerHTML = data.version;
  }
}

const updateColors = () => {
  const root = document.querySelector(':root');
  if (nightMode) {
    root.style.setProperty('--html-bg', colorsDark.htmlBg);
    root.style.setProperty('--main-bg', colorsDark.mainBg);
    root.style.setProperty('--main-shadow', colorsDark.mainShadow);
    root.style.setProperty('--main-text', colorsDark.mainText);
    root.style.setProperty('--main-logo', colorsDark.mainLogo);
    root.style.setProperty('--main-link', colorsDark.mainLink);
    root.style.setProperty('--main-red', colorsDark.mainRed);
    root.style.setProperty('--main-light', colorsDark.mainLight);
    root.style.setProperty('--new-shadow', colorsDark.newShadow);
    root.style.setProperty('--new-blue', colorsDark.newBlue);
    document.getElementById('moon-button').innerHTML = feather.icons['sun'].toSvg();
  } else {
    root.style.setProperty('--html-bg', colorsLight.htmlBg);
    root.style.setProperty('--main-bg', colorsLight.mainBg);
    root.style.setProperty('--main-shadow', colorsLight.mainShadow);
    root.style.setProperty('--main-text', colorsLight.mainText);
    root.style.setProperty('--main-logo', colorsLight.mainLogo);
    root.style.setProperty('--main-link', colorsLight.mainLink);
    root.style.setProperty('--main-red', colorsLight.mainRed);
    root.style.setProperty('--main-light', colorsLight.mainLight);
    root.style.setProperty('--new-shadow', colorsLight.newShadow);
    root.style.setProperty('--new-blue', colorsLight.newBlue);
    document.getElementById('moon-button').innerHTML = feather.icons['moon'].toSvg();
  }
}

const nightClick = () => {
  if (!nightMode) {
    nightMode = true;
    setDarkmodeParams();
    updateColors();
  } else {
    nightMode = false;
    setDarkmodeParams();
    updateColors();
  }
}

const setParam = (link, param, value) => {
  let url = new URL(link, window.location.origin);
  if (url.searchParams.has(param)) {
    url.searchParams.set(param, value);
    return url.toString();
  } else {
    url.searchParams.append(param, value);
    return url.toString();
  }
}

const setDarkmodeParams = () => {
  Array.from(document.getElementsByClassName('espweb-link'))
    .map(e => e.setAttribute('href', setParam(e.getAttribute('href'), 'darkmode', nightMode)));
}

updateColors();
setDarkmodeParams();