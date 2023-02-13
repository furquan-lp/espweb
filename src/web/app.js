console.log('begin');
feather.replace();

const colorsLight = {
  mainBg: '#f1faee',
  mainShadow: '#f1faee',
  mainText: '#1d3557',
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
  mainLink: '#e63946',
  mainRed: '#ffb703',
  mainLight: '#ffb703',
  newShadow: '#14213d',
  newBlue: '#fb8500',
  htmlBg: '#023047'
};

let jsonObject = {};
let nightMode = false;

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
  }
}

const nightClick = () => {
  const root = document.querySelector(':root');
  if (!nightMode) {
    root.style.setProperty('--html-bg', colorsDark.htmlBg);
    root.style.setProperty('--main-bg', colorsDark.mainBg);
    root.style.setProperty('--main-shadow', colorsDark.mainShadow);
    root.style.setProperty('--main-text', colorsDark.mainText);
    root.style.setProperty('--main-link', colorsDark.mainLink);
    root.style.setProperty('--main-red', colorsDark.mainRed);
    root.style.setProperty('--main-light', colorsDark.mainLight);
    root.style.setProperty('--new-shadow', colorsDark.newShadow);
    root.style.setProperty('--new-blue', colorsDark.newBlue);
    nightMode = true;
  } else {
    root.style.setProperty('--html-bg', colorsLight.htmlBg);
    root.style.setProperty('--main-bg', colorsLight.mainBg);
    root.style.setProperty('--main-shadow', colorsLight.mainShadow);
    root.style.setProperty('--main-text', colorsLight.mainText);
    root.style.setProperty('--main-link', colorsLight.mainLink);
    root.style.setProperty('--main-red', colorsLight.mainRed);
    root.style.setProperty('--main-light', colorsLight.mainLight);
    root.style.setProperty('--new-shadow', colorsLight.newShadow);
    root.style.setProperty('--new-blue', colorsLight.newBlue);
    nightMode = false;
  }
}