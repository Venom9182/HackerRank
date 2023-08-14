import React from 'react';

const DownloadButton = () => {
  const handleDownloadClick = () => {
    // Create a link to the file you want to download
    const link = document.createElement('a');
    link.href = '/path/to/your/file'; // Replace with the actual file path
    link.download = 'filename.ext'; // Replace with the desired filename
    document.body.appendChild(link);

    // Simulate a click on the link to trigger the download
    link.click();

    // Remove the link element from the DOM
    document.body.removeChild(link);
  };

  return (
    <button onClick={handleDownloadClick}>
      Download File
    </button>
  );
};

export default DownloadButton;
