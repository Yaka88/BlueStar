namespace BlueStar
{
    partial class ClientForm
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
            this.SongGridView = new System.Windows.Forms.DataGridView();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnClear = new System.Windows.Forms.Button();
            this.btnQuery = new System.Windows.Forms.Button();
            this.textName = new System.Windows.Forms.TextBox();
            this.chkVocal = new System.Windows.Forms.CheckBox();
            this.btnPause = new System.Windows.Forms.Button();
            this.btnCut = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.btnScale = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.SongGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // SongGridView
            // 
            this.SongGridView.AllowUserToAddRows = false;
            this.SongGridView.AllowUserToDeleteRows = false;
            this.SongGridView.AllowUserToOrderColumns = true;
            this.SongGridView.AllowUserToResizeRows = false;
            this.SongGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.SongGridView.Location = new System.Drawing.Point(-1, 1);
            this.SongGridView.MultiSelect = false;
            this.SongGridView.Name = "SongGridView";
            this.SongGridView.ReadOnly = true;
            this.SongGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.SongGridView.Size = new System.Drawing.Size(540, 590);
            this.SongGridView.TabIndex = 0;
            this.SongGridView.CellContentDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.SongGridView_CellContentDoubleClick);
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(544, 4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(360, 240);
            this.panel1.TabIndex = 5;
            // 
            // btnClear
            // 
            this.btnClear.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnClear.Location = new System.Drawing.Point(741, 422);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(107, 37);
            this.btnClear.TabIndex = 16;
            this.btnClear.Text = "清空";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnQuery
            // 
            this.btnQuery.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnQuery.Location = new System.Drawing.Point(591, 422);
            this.btnQuery.Name = "btnQuery";
            this.btnQuery.Size = new System.Drawing.Size(107, 37);
            this.btnQuery.TabIndex = 15;
            this.btnQuery.Text = "查询";
            this.btnQuery.UseVisualStyleBackColor = true;
            this.btnQuery.Click += new System.EventHandler(this.btnQuery_Click);
            // 
            // textName
            // 
            this.textName.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textName.Location = new System.Drawing.Point(723, 499);
            this.textName.Name = "textName";
            this.textName.Size = new System.Drawing.Size(148, 27);
            this.textName.TabIndex = 14;
            // 
            // chkVocal
            // 
            this.chkVocal.AutoSize = true;
            this.chkVocal.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.chkVocal.Location = new System.Drawing.Point(741, 352);
            this.chkVocal.Name = "chkVocal";
            this.chkVocal.Size = new System.Drawing.Size(101, 24);
            this.chkVocal.TabIndex = 13;
            this.chkVocal.Text = "原唱/伴奏";
            this.chkVocal.UseVisualStyleBackColor = true;
            this.chkVocal.CheckedChanged += new System.EventHandler(this.chkVocal_CheckedChanged);
            // 
            // btnPause
            // 
            this.btnPause.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnPause.Location = new System.Drawing.Point(591, 345);
            this.btnPause.Name = "btnPause";
            this.btnPause.Size = new System.Drawing.Size(107, 37);
            this.btnPause.TabIndex = 12;
            this.btnPause.Text = "暂停/继续";
            this.btnPause.UseVisualStyleBackColor = true;
            this.btnPause.Click += new System.EventHandler(this.btnPause_Click);
            // 
            // btnCut
            // 
            this.btnCut.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnCut.Location = new System.Drawing.Point(741, 273);
            this.btnCut.Name = "btnCut";
            this.btnCut.Size = new System.Drawing.Size(107, 37);
            this.btnCut.TabIndex = 11;
            this.btnCut.Text = "切歌";
            this.btnCut.UseVisualStyleBackColor = true;
            this.btnCut.Click += new System.EventHandler(this.btnCut_Click);
            // 
            // btnStart
            // 
            this.btnStart.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnStart.Location = new System.Drawing.Point(591, 273);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(107, 37);
            this.btnStart.TabIndex = 10;
            this.btnStart.Text = "播放";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(26, 592);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(845, 84);
            this.pictureBox1.TabIndex = 8;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseClick);
            // 
            // btnScale
            // 
            this.btnScale.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnScale.Location = new System.Drawing.Point(591, 494);
            this.btnScale.Name = "btnScale";
            this.btnScale.Size = new System.Drawing.Size(107, 37);
            this.btnScale.TabIndex = 17;
            this.btnScale.Text = "缩放";
            this.btnScale.UseVisualStyleBackColor = true;
            this.btnScale.Click += new System.EventHandler(this.btnScale_Click);
            // 
            // ClientForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(904, 684);
            this.Controls.Add(this.btnScale);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.btnQuery);
            this.Controls.Add(this.textName);
            this.Controls.Add(this.chkVocal);
            this.Controls.Add(this.btnPause);
            this.Controls.Add(this.btnCut);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.SongGridView);
            this.MaximizeBox = false;
            this.Name = "ClientForm";
            this.Text = "KTV客户点播系统";
            this.Load += new System.EventHandler(this.ClientForm_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ClientForm_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.SongGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView SongGridView;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Button btnQuery;
        private System.Windows.Forms.TextBox textName;
        private System.Windows.Forms.CheckBox chkVocal;
        private System.Windows.Forms.Button btnPause;
        private System.Windows.Forms.Button btnCut;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Button btnScale;
    }
}

