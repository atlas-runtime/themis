import {HmacSHA512} from 'benchmarks/crypto-es/lib/sha512.js';
import {AES} from 'benchmarks/crypto-es/lib/aes.js';

function encrypt(data, enc_key) {
    return AES.encrypt(data, enc_key);
}

function sign(data, sign_key) {
    return HmacSHA512(data, sign_key);
}

function encrypt_sign(data, enc_key, sign_key) {
    var s = sign(data, sign_key);
    var e = encrypt(data, enc_key);
    return e + s;
}                                       

let benchmarks = {};
benchmarks.encrypt_sign = encrypt_sign;
export {benchmarks};
