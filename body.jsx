useEffect(() => {
    // Add background class to body only on the login page
    document.body.classList.add('login-page');

    // Remove the background class when the component unmounts
    return () => {
      document.body.classList.remove('login-page');
    };
  }, []);
