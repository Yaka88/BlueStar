namespace BlueStar
{
    partial class TestForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.btnConvert = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.textGrade = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button12 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.checkVocal = new System.Windows.Forms.CheckBox();
            this.lblPosition = new System.Windows.Forms.Label();
            this.checkRecord = new System.Windows.Forms.CheckBox();
            this.checkMatch = new System.Windows.Forms.CheckBox();
            this.checkVisible = new System.Windows.Forms.CheckBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.chkMoreData = new System.Windows.Forms.CheckBox();
            this.patchButton = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.checkToWav = new System.Windows.Forms.CheckBox();
            this.butKSCFile = new System.Windows.Forms.Button();
            this.checkInvert = new System.Windows.Forms.CheckBox();
            this.textKSCFile = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnBMP = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnCopyFile = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnUpdateYwt = new System.Windows.Forms.Button();
            this.lblFreq = new System.Windows.Forms.Label();
            this.button9 = new System.Windows.Forms.Button();
            this.textSQL = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnConvert
            // 
            this.btnConvert.Location = new System.Drawing.Point(6, 10);
            this.btnConvert.Name = "btnConvert";
            this.btnConvert.Size = new System.Drawing.Size(106, 23);
            this.btnConvert.TabIndex = 0;
            this.btnConvert.Text = "Convert Wave";
            this.btnConvert.UseVisualStyleBackColor = true;
            this.btnConvert.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(9, 14);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(95, 23);
            this.button2.TabIndex = 1;
            this.button2.Text = "Match audio";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // textGrade
            // 
            this.textGrade.Location = new System.Drawing.Point(56, 37);
            this.textGrade.Name = "textGrade";
            this.textGrade.Size = new System.Drawing.Size(59, 20);
            this.textGrade.TabIndex = 2;
            this.textGrade.Text = "90";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 40);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Grade";
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(9, 14);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(106, 23);
            this.button3.TabIndex = 6;
            this.button3.Text = "Play MV";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(120, 14);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 7;
            this.button4.Text = "Stop";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button12);
            this.groupBox1.Controls.Add(this.button11);
            this.groupBox1.Controls.Add(this.button10);
            this.groupBox1.Controls.Add(this.checkVocal);
            this.groupBox1.Controls.Add(this.lblPosition);
            this.groupBox1.Controls.Add(this.checkRecord);
            this.groupBox1.Controls.Add(this.checkMatch);
            this.groupBox1.Controls.Add(this.checkVisible);
            this.groupBox1.Controls.Add(this.button4);
            this.groupBox1.Controls.Add(this.button3);
            this.groupBox1.Location = new System.Drawing.Point(3, 133);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(240, 140);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            // 
            // button12
            // 
            this.button12.Location = new System.Drawing.Point(59, 73);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(44, 23);
            this.button12.TabIndex = 18;
            this.button12.Text = ">";
            this.button12.UseVisualStyleBackColor = true;
            this.button12.Click += new System.EventHandler(this.button12_Click);
            // 
            // button11
            // 
            this.button11.Location = new System.Drawing.Point(9, 73);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(44, 23);
            this.button11.TabIndex = 17;
            this.button11.Text = "<";
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Click += new System.EventHandler(this.button11_Click);
            // 
            // button10
            // 
            this.button10.Location = new System.Drawing.Point(9, 43);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(75, 23);
            this.button10.TabIndex = 16;
            this.button10.Text = "Pause/Play";
            this.button10.UseVisualStyleBackColor = true;
            this.button10.Click += new System.EventHandler(this.button10_Click);
            // 
            // checkVocal
            // 
            this.checkVocal.AutoSize = true;
            this.checkVocal.Location = new System.Drawing.Point(120, 112);
            this.checkVocal.Name = "checkVocal";
            this.checkVocal.Size = new System.Drawing.Size(53, 17);
            this.checkVocal.TabIndex = 15;
            this.checkVocal.Text = "Vocal";
            this.checkVocal.UseVisualStyleBackColor = true;
            this.checkVocal.CheckedChanged += new System.EventHandler(this.checkVocal_CheckedChanged);
            // 
            // lblPosition
            // 
            this.lblPosition.AutoSize = true;
            this.lblPosition.Location = new System.Drawing.Point(13, 112);
            this.lblPosition.Name = "lblPosition";
            this.lblPosition.Size = new System.Drawing.Size(44, 13);
            this.lblPosition.TabIndex = 13;
            this.lblPosition.Text = "Position";
            // 
            // checkRecord
            // 
            this.checkRecord.AutoSize = true;
            this.checkRecord.Location = new System.Drawing.Point(120, 89);
            this.checkRecord.Name = "checkRecord";
            this.checkRecord.Size = new System.Drawing.Size(61, 17);
            this.checkRecord.TabIndex = 10;
            this.checkRecord.Text = "Record";
            this.checkRecord.UseVisualStyleBackColor = true;
            // 
            // checkMatch
            // 
            this.checkMatch.AutoSize = true;
            this.checkMatch.Checked = true;
            this.checkMatch.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkMatch.Location = new System.Drawing.Point(120, 65);
            this.checkMatch.Name = "checkMatch";
            this.checkMatch.Size = new System.Drawing.Size(56, 17);
            this.checkMatch.TabIndex = 9;
            this.checkMatch.Text = "Match";
            this.checkMatch.UseVisualStyleBackColor = true;
            // 
            // checkVisible
            // 
            this.checkVisible.AutoSize = true;
            this.checkVisible.Checked = true;
            this.checkVisible.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkVisible.Location = new System.Drawing.Point(120, 42);
            this.checkVisible.Name = "checkVisible";
            this.checkVisible.Size = new System.Drawing.Size(56, 17);
            this.checkVisible.TabIndex = 8;
            this.checkVisible.Text = "Visible";
            this.checkVisible.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.chkMoreData);
            this.groupBox2.Controls.Add(this.patchButton);
            this.groupBox2.Controls.Add(this.button8);
            this.groupBox2.Controls.Add(this.checkToWav);
            this.groupBox2.Controls.Add(this.butKSCFile);
            this.groupBox2.Controls.Add(this.checkInvert);
            this.groupBox2.Controls.Add(this.textKSCFile);
            this.groupBox2.Controls.Add(this.btnConvert);
            this.groupBox2.Location = new System.Drawing.Point(3, 10);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(240, 117);
            this.groupBox2.TabIndex = 9;
            this.groupBox2.TabStop = false;
            // 
            // chkMoreData
            // 
            this.chkMoreData.AutoSize = true;
            this.chkMoreData.Checked = true;
            this.chkMoreData.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkMoreData.Location = new System.Drawing.Point(140, 93);
            this.chkMoreData.Name = "chkMoreData";
            this.chkMoreData.Size = new System.Drawing.Size(71, 17);
            this.chkMoreData.TabIndex = 18;
            this.chkMoreData.Text = "Moredata";
            this.chkMoreData.UseVisualStyleBackColor = true;
            // 
            // patchButton
            // 
            this.patchButton.Location = new System.Drawing.Point(138, 37);
            this.patchButton.Name = "patchButton";
            this.patchButton.Size = new System.Drawing.Size(93, 23);
            this.patchButton.TabIndex = 17;
            this.patchButton.Text = "Patch It";
            this.patchButton.UseVisualStyleBackColor = true;
            this.patchButton.Click += new System.EventHandler(this.patchButton_Click);
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(138, 8);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(97, 23);
            this.button8.TabIndex = 16;
            this.button8.Text = "Batch Convert";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // checkToWav
            // 
            this.checkToWav.AutoSize = true;
            this.checkToWav.Location = new System.Drawing.Point(3, 94);
            this.checkToWav.Name = "checkToWav";
            this.checkToWav.Size = new System.Drawing.Size(71, 17);
            this.checkToWav.TabIndex = 14;
            this.checkToWav.Text = "To Wave";
            this.checkToWav.UseVisualStyleBackColor = true;
            // 
            // butKSCFile
            // 
            this.butKSCFile.Location = new System.Drawing.Point(6, 37);
            this.butKSCFile.Name = "butKSCFile";
            this.butKSCFile.Size = new System.Drawing.Size(75, 23);
            this.butKSCFile.TabIndex = 13;
            this.butKSCFile.Text = "select file";
            this.butKSCFile.UseVisualStyleBackColor = true;
            this.butKSCFile.Click += new System.EventHandler(this.butKSCFile_Click);
            // 
            // checkInvert
            // 
            this.checkInvert.AutoSize = true;
            this.checkInvert.Location = new System.Drawing.Point(79, 94);
            this.checkInvert.Name = "checkInvert";
            this.checkInvert.Size = new System.Drawing.Size(53, 17);
            this.checkInvert.TabIndex = 11;
            this.checkInvert.Text = "Invert";
            this.checkInvert.UseVisualStyleBackColor = true;
            // 
            // textKSCFile
            // 
            this.textKSCFile.Location = new System.Drawing.Point(2, 66);
            this.textKSCFile.Name = "textKSCFile";
            this.textKSCFile.Size = new System.Drawing.Size(225, 20);
            this.textKSCFile.TabIndex = 7;
            // 
            // timer1
            // 
            this.timer1.Interval = 200;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(244, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(720, 480);
            this.panel1.TabIndex = 10;
            this.panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseDown);
            // 
            // btnBMP
            // 
            this.btnBMP.Location = new System.Drawing.Point(114, 10);
            this.btnBMP.Name = "btnBMP";
            this.btnBMP.Size = new System.Drawing.Size(97, 23);
            this.btnBMP.TabIndex = 11;
            this.btnBMP.Text = "BMP Process";
            this.btnBMP.UseVisualStyleBackColor = true;
            this.btnBMP.Click += new System.EventHandler(this.btnBMP_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.textGrade);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Controls.Add(this.button2);
            this.groupBox3.Location = new System.Drawing.Point(8, 279);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(129, 68);
            this.groupBox3.TabIndex = 12;
            this.groupBox3.TabStop = false;
            // 
            // btnCopyFile
            // 
            this.btnCopyFile.Location = new System.Drawing.Point(9, 10);
            this.btnCopyFile.Name = "btnCopyFile";
            this.btnCopyFile.Size = new System.Drawing.Size(75, 23);
            this.btnCopyFile.TabIndex = 13;
            this.btnCopyFile.Text = "Copy File";
            this.btnCopyFile.UseVisualStyleBackColor = true;
            this.btnCopyFile.Click += new System.EventHandler(this.btnCopyFile_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btnUpdateYwt);
            this.groupBox4.Controls.Add(this.lblFreq);
            this.groupBox4.Controls.Add(this.btnCopyFile);
            this.groupBox4.Controls.Add(this.btnBMP);
            this.groupBox4.Location = new System.Drawing.Point(3, 392);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(211, 76);
            this.groupBox4.TabIndex = 14;
            this.groupBox4.TabStop = false;
            // 
            // btnUpdateYwt
            // 
            this.btnUpdateYwt.Location = new System.Drawing.Point(114, 39);
            this.btnUpdateYwt.Name = "btnUpdateYwt";
            this.btnUpdateYwt.Size = new System.Drawing.Size(91, 23);
            this.btnUpdateYwt.TabIndex = 15;
            this.btnUpdateYwt.Text = "Update Ywt";
            this.btnUpdateYwt.UseVisualStyleBackColor = true;
            this.btnUpdateYwt.Click += new System.EventHandler(this.btnUpdateYwt_Click);
            // 
            // lblFreq
            // 
            this.lblFreq.AutoSize = true;
            this.lblFreq.Location = new System.Drawing.Point(13, 45);
            this.lblFreq.Name = "lblFreq";
            this.lblFreq.Size = new System.Drawing.Size(28, 13);
            this.lblFreq.TabIndex = 14;
            this.lblFreq.Text = "Freq";
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(143, 324);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(87, 23);
            this.button9.TabIndex = 16;
            this.button9.Text = "Execute SQL";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // textSQL
            // 
            this.textSQL.Location = new System.Drawing.Point(9, 366);
            this.textSQL.Name = "textSQL";
            this.textSQL.Size = new System.Drawing.Size(225, 20);
            this.textSQL.TabIndex = 17;
            // 
            // TestForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(964, 480);
            this.Controls.Add(this.textSQL);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "TestForm";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnConvert;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox textGrade;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox checkVisible;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox checkMatch;
        private System.Windows.Forms.CheckBox checkRecord;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TextBox textKSCFile;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button btnBMP;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnCopyFile;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label lblFreq;
        private System.Windows.Forms.CheckBox checkInvert;
        private System.Windows.Forms.Button btnUpdateYwt;
        private System.Windows.Forms.Label lblPosition;
        private System.Windows.Forms.Button butKSCFile;
        private System.Windows.Forms.CheckBox checkToWav;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.CheckBox checkVocal;
        private System.Windows.Forms.TextBox textSQL;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button patchButton;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.CheckBox chkMoreData;
    }
}

