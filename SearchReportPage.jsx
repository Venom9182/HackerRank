import React from 'react';
import './SearchReportPage.css'; // Import your CSS file

function SearchReportPage() {
  return (
    <div className="container">
      <div className="search-form">
        <h2>Search Report</h2>
        <div className="input-group">
          <label>Category:</label>
          {/* Dropdown for Category */}
          <div className="dropdown">
            <button className="dropbtn">Select Category</button>
            <div className="dropdown-content">
              {/* Category options */}
              <a href="#">Option 1</a>
              <a href="#">Option 2</a>
              <a href="#">Option 3</a>
            </div>
          </div>
        </div>
        <div className="input-group">
          <label>File Type:</label>
          {/* Dropdown for File Type */}
          <div className="dropdown">
            <button className="dropbtn">Select File Type</button>
            <div className="dropdown-content">
              {/* File Type options */}
              <a href="#">Option 1</a>
              <a href="#">Option 2</a>
              <a href="#">Option 3</a>
            </div>
          </div>
        </div>
        <div className="input-group">
          <label>Start Date:</label>
          {/* Calendar component */}
          <input type="date" />
        </div>
        <div className="input-group">
          <label>End Date:</label>
          {/* Calendar component */}
          <input type="date" />
        </div>
        <div className="input-group">
          <label>Client ID:</label>
          {/* Numerical input */}
          <input type="number" />
        </div>
        <button className="search-button">Search</button>
      </div>
    </div>
  );
}

export default SearchReportPage;
