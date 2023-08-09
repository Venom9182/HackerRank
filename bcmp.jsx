import React from 'react';
import './SearchReportPage.css'; // Import your CSS file

function SearchReportPage() {
  return (
    <div className="form-container">
      <h2>Search Report</h2>
      <form action="process_form.php" method="post">
        <label htmlFor="category">Category:</label>
        <select id="category" name="category">
          <option value="" disabled selected>Choose</option>
          <option value="finance">Finance</option>
          <option value="operation">Operation</option>
          <option value="compliance">Compliance</option>
        </select>

        <label htmlFor="fileType">File Type:</label>
        <select id="fileType" name="fileType">
          <option value="" disabled selected>Choose</option>
          <option value=".csf">.csf</option>
          <option value=".pdf">.pdf</option>
          <option value=".docx">.docx</option>
        </select>

        <label htmlFor="startDate">Start Date:</label>
        <input type="date" id="startDate" name="startDate" />

        <label htmlFor="endDate">End Date:</label>
        <input type="date" id="endDate" name="endDate" />

        <label htmlFor="clientid">Client Id:</label>
        <input type="text" id="clientid" name="clientid" /><br /><br />

        <button type="submit">Search</button>
      </form>
    </div>
  );
}

export default SearchReportPage;
