const isProd = import.meta.env.PROD;

const conf = {
    isProd,
    apiPrefix: isProd? 'http://localhost:1337' : 'http://localhost:1337'
}

export default conf;