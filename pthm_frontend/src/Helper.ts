import { useLocation, useNavigate } from "react-router-dom"
import { useEffect } from "react"
import CryptoJS from 'crypto-js';
import toast from "react-hot-toast";
import { useState } from "react";

export const ScrollToTop = () => {
    const {pathname} = useLocation()

    useEffect(() => {
        window.scrollTo(0, 0)
    }, [pathname])
    
    return null
}
const secretKey = import.meta.env.VITE_SECRET_KEY

export const storeUser = (data:any) => {
    console.log(import.meta.env.VITE_SECRET_KEY)
    const encryptedData = CryptoJS.AES.encrypt(
        JSON.stringify({
            id: data.user.id,
            username: data.user.username,
            avatar: data.user.avatar,
            userComments: data.user.userComments,
            userArticles: data.user.userArticles,
            jwt: data.jwt
        }),
        secretKey
    ).toString();

    sessionStorage.setItem('user', encryptedData)
}

export const userData = () => {
    const encryptedData = sessionStorage.getItem('user');
    if (encryptedData) {
        try {
            CryptoJS.AES.decrypt(encryptedData, secretKey).toString(CryptoJS.enc.Utf8);
        } catch {
            toast.error("Something went wrong, please Sign in again");
            sessionStorage.removeItem('user');
            return
        }
        const bytes = CryptoJS.AES.decrypt(encryptedData, secretKey);
        const decryptedData = JSON.parse(bytes.toString(CryptoJS.enc.Utf8));
        return decryptedData;
    } else {
        return false;
    }

};

type Props = {
    children: JSX.Element
}

export const ProtectRoute = ({ children }: Props) => {
    const navigate = useNavigate();
    const [loading, setLoading] = useState(true);
    const [isAuthenticated, setIsAuthenticated] = useState(false);

    useEffect(() => {
        const data = userData();
        if (!data?.jwt) {
            navigate("/signin");
        } else {
            setIsAuthenticated(true);
        }
        setLoading(false);
    }, [navigate]);

    if (loading) return null; // Prevents flickering

    return isAuthenticated ? children : null;
};

export const Signout = () => {
    sessionStorage.removeItem('user');
    toast.success("Sign Out Successful.");
    const navigate = useNavigate();
    navigate("/signin");
    return
}
  
  